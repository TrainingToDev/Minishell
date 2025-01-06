#include "minishell.h"

static t_hdc	*init_heredoc(void)
{
	t_hdc	*content;

	content = malloc(sizeof(t_hdc));
	if (!content)
		return (NULL);
	content->lines = NULL;
	content->count = 0;
	return (content);
}
static char	**split_lines(const char *input)
{
	char	**lines;

	lines = ft_split(input, '\n');
	if (!lines)
		return (NULL);
	return (lines);
}

t_hdc	*get_heredoc_lines(const char *input, const char *delimiter)
{
	t_hdc	*content;
	char	**lines;

	if (!input || !delimiter)
		return (NULL);
	content = init_heredoc();
	if (!content)
		return (NULL);
	lines = split_lines(input);
	if (!lines)
	{
		free(content);
		return (NULL);
	}
	if (get_lines(content, lines, delimiter) == -1)
	{
		free_heredoc_content(content);
		free_split(lines);
		return (NULL);
	}
	free_split(lines);
	return (content);
}

int	get_lines(t_hdc *content, char **lines, const char *delimiter)
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
		if (ft_strcmp(lines[i], delimiter) == 0)
			return (0);
		i++;
	}
	return (0);
}
