/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:07 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/01 23:44:15 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_pipe(t_redir *cur)
{
	int		pipefd[2];
	size_t	i;
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	i = 0;
	while (i < cur->content->count)
	{
		line = cur->content->lines[i];
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		i++;
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		print_error(E_DUPFD, "heredoc", ERR_G);
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}

int process_heredoc(t_redir *cur, t_minishell *shell, int mode, int f)
{
	int ret;

	if (!cur->content)
	{
		print_error(E_NOMEM, "HEREDOC: invalid content", ERR_SEGV);
		return (-1);
	}
	if (f)
	{
		if (cur->content->count > 0)
			ret = forked_heredoc(cur->content, cur->filename, shell, 1);
		else
			ret = forked_heredoc(cur->content, cur->filename, shell, 0);
	}
	else
	{
		if (cur->content->count > 0)
			heredoc_copied(cur->content, cur->filename, shell);
		else
			heredoc_interactive(cur->filename, cur->content, shell);
	}
	if (mode)
		return heredoc_pipe(cur);
	else
		return (ret);
}

int	process_redir_in(t_redir *current, int mode)
{
	int	fd;

	fd = open_input(current->filename);
	if (fd == -1)
		return (-1);
	if (mode)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			print_error(E_DUPFD, current->filename, ERR_G);
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
		print_error(E_CMD, current->filename, ERR_G);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (-1);
	}
	if (mode)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			print_error(E_DUPFD, current->filename, ERR_G);
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
		print_error(E_CMD, current->filename, ERR_G);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (-1);
	}
	if (mode)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			print_error(E_DUPFD, current->filename, ERR_G);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}
