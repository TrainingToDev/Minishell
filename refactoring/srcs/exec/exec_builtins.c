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

int	execute_builtin_cmd(t_command *command, t_minishell *shell, int fork_required)
{
	int	exit_status;

	if (!fork_required)
	{
		if (apply_builtins_redir(command->redirs, shell) == -1)
			return (1);
		exit_status = execute_builtin(shell, command->argv);
		if (dup2(shell->fd_output, STDOUT_FILENO) == -1)
		{
			perror("dup2 restore");
			return (1);
		}
		return (exit_status);
	}
	else
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			if (apply_redirections(command->redirs, shell, 1) == -1)
			{
				perror("Error apply redir!!!");
				exit(1);
			}
			exit(execute_builtin(shell, command->argv));
		}
		else if (pid < 0)
		{
			perror("fork");
			return 1;
		}
		waitpid(pid, &shell->last_exit_status, 0);
		return WEXITSTATUS(shell->last_exit_status);
	}
}
