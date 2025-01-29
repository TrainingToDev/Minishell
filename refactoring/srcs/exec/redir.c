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

#include "minishell.h"

static int	handle_redir_in(t_redir *current)
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

int	handle_redir_out(t_redir *redir)
{
	int	fd;

	if (!redir->filename)
	{
		perror("Redirection OUT: Filename is NULL");
		return (-1);
	}
	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Failed to open file for REDIR_OUT");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect stdout for REDIR_OUT");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_append(t_redir *current)
{
	int	fd;

	fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		perror(current->filename);
		if (fd != -1)
			close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirections(t_redir *redirs, t_minishell *shell)
{
	t_redir	*current;

	// Priority 1 : HEREDOCS
	current = redirs;
	while (current)
	{
		if (current->type == REDIR_HEREDOC)
		{
			if (heredoc_redir(current, shell) == -1)
				return (-1);
		}
		current = current->next;
	}

	// Priority 2 : REDIR_IN
	current = redirs;
	while (current)
	{
		if (current->type == REDIR_IN)
		{
			if (handle_redir_in(current) == -1)
				return (-1);
		}
		current = current->next;
	}

	// Priority 3 : REDIR_OUT et REDIR_APPEND
	current = redirs;
	while (current)
	{
		if (current->type == REDIR_OUT)
		{
			if (handle_redir_out(current) == -1)
				return (-1);
		}
		else if (current->type == REDIR_APPEND)
		{
			if (handle_redir_append(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
