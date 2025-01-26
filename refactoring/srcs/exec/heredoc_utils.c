/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:08:37 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 16:42:18 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *process_input_line(char *line, const char *delim, t_minishell *shell)
{
    char	*expanded_line;

	expanded_line = NULL;
    if (ft_strcmp(line, delim) == 0)
	{
        free(line);
        return (NULL);
    }
    expanded_line = expand_variables_in_str(line, shell);
    free(line);
    if (!expanded_line)
	{
        perror("expand_variables_in_str");
    }
    return (expanded_line);
}
