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
	{
		// perror("pipe failed");
		print_error(E_PIPE, "heredoc", ERR_G);
		return (-1);
	}
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
		// perror("dup2");
		print_error(E_DUPFD, "heredoc", ERR_G);
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}

int	process_heredoc(t_redir *cur, t_minishell *shell, int mode)
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
	if (mode)
		return (heredoc_pipe(cur));
	else
		return (0);
}

// Process REDIR_IN
// if mode == 1, check dup2(fd, STDIN_FILENO) or write in pipe for heredoc 
// else if, open/ferme it

int process_redir_in(t_redir *current, int mode)
{
	int	fd;

	fd = open(current->filename, O_RDONLY);
	if (fd == -1)
	{
		// printf("-1\n");
		// print_error(E_NODIR, current->filename, 1); // cat <err
		perror(current->filename);
		status_manager(1, STATUS_WRITE);
		return (1);
	}
	if (mode)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			// perror(current->filename);
			print_error(E_DUPFD, current->filename, ERR_G);
			// printf("in\n");
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
		// printf("-2\n");
		// perror(current->filename); // ok | test3
		print_error(E_CMD, current->filename, ERR_G);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (-1);
	}
	if (mode)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			// perror(current->filename);
			print_error(E_DUPFD, current->filename, ERR_G);
			// printf("out\n");
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
		// printf("-3\n");
		print_error(E_CMD, current->filename, ERR_G);
		// perror(current->filename);
		return (-1);
	}
	if (mode)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			// perror(current->filename);
			print_error(E_DUPFD, current->filename, ERR_G);
			// printf(">>\n");
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}
