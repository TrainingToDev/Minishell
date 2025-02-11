/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:31:57 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/09 20:16:42 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int heredoc_redir(t_redir *redirs, t_minishell *shell)
{
    t_redir	*current;
    int ret;

	current = redirs;
    ret = 0;
    while (current)
    {
        if (current->type == REDIR_HEREDOC)
        {
            ret = heredoc(current, shell);
            if (ret < 0)
                return (-1);
        }
        current = current->next;
    }
    return (ret);
}

static int output_redir(t_redir *redirs, t_minishell *shell)
{
    if (redirs->type == REDIR_APPEND)
    {
        if (redir_append(redirs, shell) == -1)
            return (-1);   
    }
    else
    {
        if (redir_out(redirs, shell) == -1)
            return (-1);
    }
    return(0);
}

int redirections(t_redir *redirs, t_minishell *shell)
{
    t_redir *current;
    int temp;

    current = redirs;
    temp = heredoc_redir(redirs, shell);
    if (temp != 0)
        return(temp);
    while(current)
    {
        if (current->type == REDIR_OUT || current->type == REDIR_APPEND)
        {
            if (output_redir(current, shell) == -1)
                return (-1);
        }
        if (current->type == REDIR_IN)
        {
            if (redir_in(current, shell) == -1)
                return (-1);
        }
        current = current->next;
    }
    return(0);
}
