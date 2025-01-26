/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:24:20 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 16:30:51 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_final_delimiter(t_hdc *content, const char *delim)
{
    if (content->count > 0 
		&& ft_strcmp(content->lines[content->count - 1], delim) == 0)
	{
        free(content->lines[content->count - 1]);
        content->lines[content->count - 1] = NULL;
        content->count--;
    }
}

static int read_and_expand(t_hdc *content, const char *delim, t_minishell *shell)
{
	char	*expanded_line;
	char	*line;

    while (1)
	{
		line = read_user_input(delim, shell);
		if (!line)
			break ;
        if (ft_strcmp(line, delim) == 0)
		{
            free(line);
            break ;
        }
        expanded_line = expand_variables_in_str(line, shell);
        free(line);
        if (!expanded_line)
            return (0);
        if (!append_line(content, expanded_line))
		{
            free(expanded_line);
            return (0);
        }
    }
    return (1);
}

static int expand_existing_lines(t_hdc *content, t_minishell *shell)
{
	char	*expanded_line;
	size_t	i;

	i = 0;
    while (i < content->count)
	{
        expanded_line = expand_variables_in_str(content->lines[i], shell);
        if (!expanded_line)
		{
            perror("expand_variables_in_str");
            return 0;
        }
        free(content->lines[i]);
        content->lines[i] = expanded_line;
		i++;
    }
    return (1);
}

static int check_params(t_hdc *content, const char *delim, t_minishell *shell)
{
    if (!content || !delim || !shell)
	{
        fprintf(stderr, "Invalid parameters provided to handle_interactive_heredoc.\n");
        return (0);
    }
    return (1);
}

void handle_copied_heredoc(t_hdc *content, const char *delim, t_minishell *shell)
{
    if (!check_params(content, delim, shell))
		return ;
	main_heredoc(); // Configure signals for heredoc mode
    if (!expand_existing_lines(content, shell))
		return ;
    if (content->count == 0 
		|| ft_strcmp(content->lines[content->count - 1], delim) != 0)
		{
			if (!read_and_expand(content, delim, shell))
				return ;
    }
    remove_final_delimiter(content, delim);
}
