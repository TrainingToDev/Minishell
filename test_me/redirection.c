/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:00:19 by herandri          #+#    #+#             */
/*   Updated: 2024/11/14 13:33:03 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// first implementation for redir, need refactoring

int setup_redirections(t_command *cmd)
{
    t_redirection *redir;
    int fd;

    redir = cmd->redirs;
    while (redir)
    {
        if (redir->type == REDIR_IN)
            fd = open(redir->filename, O_RDONLY);
        else if (redir->type == REDIR_OUT)
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (redir->type == REDIR_APPEND)
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (redir->type == REDIR_HEREDOC)
            fd = handle_heredoc(redir);
        else
            return (-1);
        if (fd < 0)
        {
            perror(redir->filename);
            return (-1);
        }
        if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
            dup2(fd, STDIN_FILENO);
        else
            dup2(fd, STDOUT_FILENO);
        close(fd);
        redir = redir->next;
    }
    return (0);
}

int handle_heredoc(t_redirection *redir)
{
    int     fd[2];
    char    *line;

    if (pipe(fd) < 0)
        return (perror("pipe"), -1);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, redir->filename) == 0)
            break ;
        ft_putendl_fd(line, fd[1]);
        free(line);
    }
    free(line);
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    return (0);
}
