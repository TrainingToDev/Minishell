/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:31:57 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/01 23:42:41 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int heredoc_redir(t_redir *redirs, t_minishell *shell, int mode, int f)
{
    t_redir	*current;

	current = redirs;
    while (current)
    {
        if (current->type == REDIR_HEREDOC)
        {
            if (process_heredoc(current, shell, mode, f) == -1)
                return (-1);
        }
        current = current->next;
    }
    return (0);
}

static int input_redir(t_redir *redirs, int mode)
{
    t_redir	*current;

	current = redirs;
    while (current)
    {
        if (current->type == REDIR_IN)
        {
            if (process_redir_in(current, mode) == -1)
                return (-1);
        }
        current = current->next;
    }
    return (0);
}

static int output_redir(t_redir *redirs, int mode)
{
    t_redir	*current;

	current = redirs;
    while (current)
    {
        if (current->type == REDIR_OUT)
        {
            if (process_redir_out(current, mode) == -1)
                return (-1);
        }
        else if (current->type == REDIR_APPEND)
        {
            if (process_redir_append(current, mode) == -1)
                return (-1);
        }
        current = current->next;
    }
    return (0);
}

int apply_redirections(t_redir *redirs, t_minishell *shell, int mode, int f)
{
    if (heredoc_redir(redirs, shell, mode, f) == -1)
        return (-1);
    if (input_redir(redirs, mode) == -1)
        return (-1);
    if (output_redir(redirs, mode) == -1)
        return (-1);
    return (0);
}
