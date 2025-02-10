/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:03:35 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 12:51:03 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin_no_fork(t_command *cmd, t_minishell *shell)
{
	int	exit_status;

	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		if (exit_input(cmd->redirs) == -1)
			return (1);
		exit_output(cmd->redirs);
		return (ft_exit(shell, cmd->argv));
	}
	if (apply_builtins_redir(cmd->redirs, shell) == -1)
		return (1);
	exit_status = execute_builtin(shell, cmd->argv);
	if (dup2(shell->fd_output, STDOUT_FILENO) == -1)
	{
		print_error(E_DUPFD, "not restore stdout", ERR_G);
		return (1);
	}
	status_manager(exit_status, STATUS_WRITE);
	return (exit_status);
}

static int	execute_builtin_with_fork(t_command *cmd, t_minishell *shell)
{
	int		exit_status;
	pid_t	pid;

	pid = fork();
	if (pid == 0) 
	{
		if (apply_redir(cmd->redirs, shell, 1, 1) == 0)
			exit(1);
		exit_status = execute_builtin(shell, cmd->argv);
		if (exit_status == -1)
			exit(1);
		status_manager(exit_status, STATUS_WRITE);
		exit(exit_status);
	}
	else if (pid < 0)
	{
		print_error(E_FORK, "fork", ERR_G);
		return (1);
	}
	waitpid(pid, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
	status_manager(exit_status, STATUS_WRITE);
	return (exit_status);
}

int	execute_builtin_cmd(t_command *cmd, t_minishell *shell, int fork_required)
{
	if (!fork_required)
		return (execute_builtin_no_fork(cmd, shell));
	else
		return (execute_builtin_with_fork(cmd, shell));
}

static int input_error(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
		{
			print_error(E_CMD, filename, ERR_G);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		}
		else if (errno == EACCES)
		{
			print_error(E_CMD, filename, ERR_G);
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
		}
		else
		{
			print_error(E_CMD, filename, ERR_G);
			ft_putendl_fd(": error Unknown", STDERR_FILENO);
		}
		return (-1);
	}
	close(fd);
	return (0);
}

int	exit_input(t_redir *redirs)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (current->type == REDIR_IN)
		{
			if (input_error(current->filename) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
