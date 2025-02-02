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

// Process REDIR_IN | REDIR_OUT | REDIR_APPEND
// if mode == 1, check dup2(fd, STDIN_FILENO) or write in pipe for heredoc 
// else if, open/close it

int process_redir_in(t_redir *current, int mode)
{
	int	fd;

	fd = open(current->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(current->filename);
		return (-1);
	}
	if (mode)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror(current->filename);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}

int process_redir_out(t_redir *current, int mode)
{
	int	fd;

	fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(current->filename);
		return (-1);
	}
	if (mode)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror(current->filename);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}

int	process_redir_append(t_redir *current, int mode)
{
	int	fd;

	fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(current->filename);
		return (-1);
	}
	if (mode)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror(current->filename);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}

int apply_redirections(t_redir *redirs, t_minishell *shell, int mode)
{
    t_redir *current;

    /* Priority 1 : HEREDOC */
    current = redirs;
    while (current)
    {
        if (current->type == REDIR_HEREDOC)
        {
            if (process_heredoc(current, shell, mode) == -1)
                return (-1);
        }
        current = current->next;
    }
    
    /* Priority 2 : REDIR_IN */
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
    
    /* Priority 3 : REDIR_OUT et REDIR_APPEND */
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
