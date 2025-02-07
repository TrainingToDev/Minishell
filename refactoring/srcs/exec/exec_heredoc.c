/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 14:14:26 by miaandri          #+#    #+#             */
/*   Updated: 2025-02-07 14:14:26 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int for_parent()
{
    int fd;

    fd = open("herdoc_temp", O_RDONLY);
    if (fd < 0)
        return (1);
    close(fd);
    return(0);
}

static int heredoc(t_redir *cur, t_minishell *shell)
{
    int pid;

    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == 0)
    {
        if (!cur->content)
        {
            print_error(E_NOMEM, "HEREDOC:invalid content", ERR_SEGV);
            return (-1);
        }
        if (cur->content->count > 0)
            heredoc_copied(cur->content, cur->filename, shell);
        else
            heredoc_interactive(cur->filename, cur->content, shell);
        exit (0);
    }
    if (pid > 0)
    {
       waitpid(pid, NULL, 0);
        if (for_parent() == 0)
            return (130);
            //status_manager(130, STATUS_WRITE);
    }
    return(0);
}

static int redir_heredoc(t_redir *redirs, t_minishell *shell)
{
    t_redir	*current;
    int temp;

	current = redirs;
    temp = 0;
    while (current)
    {
        if (current->type == REDIR_HEREDOC)
        {
            temp = heredoc(current, shell);
            if (temp == -1)
                return(-1);
        }
        current = current->next;
    }
    return (temp);
}

int redir(t_redir *redirs, t_minishell *shell)
{
    if (redir_heredoc(redirs, shell) == -1)
        return(-1);
    return(0);
}