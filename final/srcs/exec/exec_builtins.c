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
		if (apply_redir(cmd->redirs, shell, 1, 0) == -1)
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
		return execute_builtin_no_fork(cmd, shell);
	else
		return execute_builtin_with_fork(cmd, shell);
}
