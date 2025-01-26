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

static char *process_input_line(char *line, const char *delim, t_minishell *shell)
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

void handle_interactive_heredoc(const char *delim, t_hdc *content, t_minishell *shell)
{
	char	*line;
	char	*expanded_line;

	if (!check_params(content, delim, shell))
		return ;
	main_heredoc(); //signal
	while (1)
	{
		line = read_user_input(delim, shell);
		if (!line)
			break;
		expanded_line = process_input_line(line, delim, shell);
		if (!expanded_line)
			break;
		if (!append_line(content, expanded_line))
			break;
    }
}
