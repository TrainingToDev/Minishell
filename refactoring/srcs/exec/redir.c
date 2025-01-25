/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:31:57 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 16:21:39 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int handle_redir_in(t_redir *current)
{
    int	fd;

	fd = open(current->filename, O_RDONLY);
    if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
	{
        perror(current->filename);
        if (fd != -1)
            close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

static int handle_redir_out(t_redir *current)
{
    int fd;

	fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
        perror(current->filename);
        if (fd != -1)
            close(fd);
        return (-1);
    }
    close(fd);
    return 0;
}

static int handle_redir_append(t_redir *current)
{
    int fd;

	fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1) {
        perror(current->filename);
        if (fd != -1)
            close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

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