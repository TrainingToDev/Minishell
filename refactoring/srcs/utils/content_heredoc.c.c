/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plou.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 01:56:35 by herandri          #+#    #+#             */
/*   Updated: 2025/01/23 23:37:10 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void free_heredoc_content(t_hdc *cnt)
{
	size_t	i;

	if (!cnt || !cnt->lines)
		return ;
	i = 0;
	while (i < cnt->count)
	{
		free(cnt->lines[i]);
		i++;
	}
	free(cnt->lines);
	cnt->lines = NULL;
	cnt->count = 0;
}

void	print_heredoc_content(t_hdc *cnt)
{
	size_t	i;
	if (!cnt)
	{
		printf("No heredoc cnt to display.\n");
		return ;
	}
	if (!cnt->lines || cnt->count == 0)
	{
		printf("Heredoc cnt is empty.\n");
		return ;
	}
	printf("Heredoc cnt (%zu lines):\n", cnt->count);
	i = 0;
	while (i < cnt->count)
	{
		printf("Line %zu: %s\n", i + 1, cnt->lines[i]);
		i++;
	}
}

t_hdc	*init_heredoc(void)
{
	t_hdc	*cnt;

	cnt = malloc(sizeof(t_hdc));
	if (!cnt)
		return (NULL);
	cnt->lines = NULL;
	cnt->count = 0;
	return (cnt);
}

char	**split_lines(char *input)
{
	char	**lines;

	lines = ft_split(input, '\n');
	if (!lines)
		return (NULL);
	return (lines);
}

static char **dup_lines(t_hdc *cnt, char *line)
{
	char	**new_lines;
	size_t	j;

	new_lines = malloc(sizeof(char *) * (cnt->count + 1));
	if (!new_lines)
		return (NULL);
	j = 0;
	while (j < cnt->count)
	{
		new_lines[j] = cnt->lines[j];
		j++;
	}
	free(cnt->lines);
	new_lines[cnt->count] = ft_strdup(line);
	if (!new_lines[cnt->count])
	{
		while (j-- > 0)
			free(new_lines[j]);
		free(new_lines);
		return (NULL);
	}
	return (new_lines);
}

int	add_line(t_hdc *cnt, char *line)
{
	char	**new_lines;

	new_lines = dup_lines(cnt, line);
	if (!new_lines)
		return (-1);

	cnt->lines = new_lines;
	cnt->count++;
	return (0);
}


int	get_lines(t_hdc *cnt, char **lines, char *dlim)
{
	size_t	i;

	i = 1;
	while (lines[i])
	{
		if (add_line(cnt, lines[i]) == -1)
		{
			free_heredoc_content(cnt);
			return (-1);
		}
		if (ft_strcmp(lines[i], dlim) == 0)
			return (0);
		i++;
	}
	return (0);
}

//print heredoc
void	process_heredoc(t_token *tokens, char *input)
{
	t_token	*current;
	t_hdc	*cnt;
	char	*dlim;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (current->next)
				dlim = current->next->value;
			else
				dlim = NULL;
			if (dlim)
			{
				printf("Handling heredoc with dlim: %s\n", dlim);
				cnt = get_heredoc_lines(input, dlim);
				if (cnt)
				{
					print_heredoc_content(cnt);
					free_heredoc_content(cnt);
					free(cnt);
				}
			}
		}
		current = current->next;
	}
}

