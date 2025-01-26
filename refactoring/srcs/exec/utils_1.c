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
