/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:39:22 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 16:43:29 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_params(t_hdc *content, const char *delim, t_minishell *shell)
{
    if (!content || !delim || !shell)
	{
        fprintf(stderr, "Invalid parameters provided to handle_interactive_heredoc.\n");
        return (0);
    }
    return (1);
}

char *read_user_input(const char *delim, t_minishell *shell)
{
    char		*line;

	line = readline("\001"COLOR_BLUE"\002""heredoc> ""\001"COLOR_RESET"\002");
   if (!line) // EOF (Ctrl+D)
    {
        fprintf(stderr, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",
                shell->nb_line_heredoc , delim);
    }
    return (line);
}

int append_line(t_hdc *content, char *line)
{
    char	**new_lines;
	size_t	i;

	new_lines = malloc(sizeof(char *) * (content->count + 1));
    if (!new_lines)
	{
        perror("malloc");
        free(line);
        return (0);
    }
	i = 0;
    while (i < content->count)
	{
        new_lines[i] = content->lines[i];
		i++;
    }
    new_lines[content->count] = line;
    free(content->lines);
    content->lines = new_lines;
    content->count++;
    return (1);
}

t_hdc	*get_heredoc_lines(const char *input, const char *delim)
{
	t_hdc	*content;
	char				**lines;

	if (!input || !delim)
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
	if (get_lines(content, lines, delim) == -1)
	{
		free_heredoc_content(content);
		free_split(lines);
		free(content);
		return (NULL);
	}
	free_split(lines);
	return (content);
}
