/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:31:57 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 09:36:29 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int apply(t_redir *redirs, t_minishell *shell)
{
    t_redir *current;
    int result;

    current = redirs;
    while (current)
    {
        result = 0;
        if (current->type == REDIR_IN)
           result = handle_redir_in(current);
        else if (current->type == REDIR_HEREDOC)
            result = handle_redir_heredoc(current, shell);
        if (result == -1)
            return (-1);
        current = current->next;
    }
    return (0);
}


int apply_redirections(t_redir *redirs, t_minishell *shell)
{
    t_redir *current;
    int result;

    if (apply(redirs, shell) == -1)
        return (-1);
    current = redirs;
    while (current)
    {
        result = 0;
        if (current->type == REDIR_OUT)
            result = handle_redir_out(current);
        else if (current->type == REDIR_APPEND)
            result = handle_redir_append(current);
        if (result == -1)
            return (-1);
        current = current->next;
    }
    return (0);
}