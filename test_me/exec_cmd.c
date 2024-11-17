/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:14:06 by herandri          #+#    #+#             */
/*   Updated: 2024/11/17 11:53:31 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need refactoring
// exec for cmd internal
int execute_command(t_minishell *shell, t_command *cmd)
{
	int status;

	status = 0;
	if (setup_redirections(cmd) != 0)
		return (-1);
	expand_arguments(shell, cmd);
	if (cmd->argv[0] == NULL)
	{
		restore_std_fds();
		return (0);
	}
	if (is_builtin(cmd->argv[0]))
		status = execute_builtin(shell, cmd);
	else
		status = execute_external(shell, cmd);
	restore_std_fds();
	return (status);
}
// for cmd external
int execute_external(t_minishell *shell, t_command *cmd)
{
	char    **envp;
	char    *path;
	pid_t   pid;

	pid = fork();
	if (pid == 0)
	{
		envp = env_list_to_envp(shell->env_list); // ...
		path = find_executable(cmd->argv[0], shell);
		if (!path)
		{
			perror("command not found");
			exit(127); // test code
		}
		execve(path, cmd->argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &shell->last_exit_status, 0);
	return (WEXITSTATUS(shell->last_exit_status));
}
