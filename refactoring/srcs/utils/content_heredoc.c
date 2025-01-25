#include "minishell.h"

void free_split(char **split)
{
	size_t i;

	if (!split)
		return;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void free_heredoc_content(t_hdc *content)
{
	size_t	i;

	if (!content || !content->lines)
		return ;
	i = 0;
	while (i < content->count)
	{
		free(content->lines[i]);
		i++;
	}
	free(content->lines);
	content->lines = NULL;
	content->count = 0;
}

void	print_heredoc_content(const t_hdc *content)
{
	size_t	i;
	if (!content)
	{
		printf("No heredoc content to display.\n");
		return ;
	}
	if (!content->lines || content->count == 0)
	{
		printf("Heredoc content is empty.\n");
		return ;
	}
	printf("Heredoc content (%zu lines):\n", content->count);
	i = 0;
	while (i < content->count)
	{
		printf("Line %zu: %s\n", i + 1, content->lines[i]);
		i++;
	}
}

t_hdc	*init_heredoc(void)
{
	t_hdc	*content;

	content = malloc(sizeof(t_hdc));
	if (!content)
		return (NULL);
	content->lines = NULL;
	content->count = 0;
	return (content);
}

char	**split_lines(const char *input)
{
	char	**lines;

	lines = ft_split(input, '\n');
	if (!lines)
		return (NULL);
	return (lines);
}

static char **dup_lines(t_hdc *content, const char *line)
{
	char	**new_lines;
	size_t	j;

	new_lines = malloc(sizeof(char *) * (content->count + 1));
	if (!new_lines)
		return (NULL);
	j = 0;
	while (j < content->count)
	{
		new_lines[j] = content->lines[j];
		j++;
	}
	free(content->lines);
	new_lines[content->count] = ft_strdup(line);
	if (!new_lines[content->count])
	{
		while (j-- > 0)
			free(new_lines[j]);
		free(new_lines);
		return (NULL);
	}
	return (new_lines);
}

int	add_line(t_hdc *content, const char *line)
{
	char	**new_lines;

	new_lines = dup_lines(content, line);
	if (!new_lines)
		return (-1);

	content->lines = new_lines;
	content->count++;
	return (0);
}


int	get_lines(t_hdc *content, char **lines, const char *delim)
{
	size_t	i;

	i = 1;
	while (lines[i])
	{
		if (add_line(content, lines[i]) == -1)
		{
			free_heredoc_content(content);
			return (-1);
		}
		if (ft_strcmp(lines[i], delim) == 0)
			return (0);
		i++;
	}
	return (0);
}

//print heredoc
void	process_heredoc(const t_token *tokens, const char *input)
{
	const t_token		*current;
	t_hdc	*content;
	char				*delim;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (current->next)
				delim = current->next->value;
			else
				delim = NULL;
			if (delim)
			{
				printf("Handling heredoc with delim: %s\n", delim);
				content = get_heredoc_lines(input, delim);
				if (content)
				{
					print_heredoc_content(content);
					free_heredoc_content(content);
					free(content);
				}
			}
		}
		current = current->next;
	}
}
