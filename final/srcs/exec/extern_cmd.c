/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:51:12 by herandri          #+#    #+#             */
/*   Updated: 2025/02/08 09:39:28 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dir_error(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	exec_child(char *path, t_command *cmd, t_minishell *shell, int f)
{
	char	**env_array;

	setup_child();

	if (apply_redir(cmd->redirs, shell, 1, f) == -1)
	{
		// print_error(E_DIR, cmd->redirs->filename, ERR_G);
		// ft_putendl_fd(": No such file or directory!!!", STDERR_FILENO);
		exit(1);
	}
	env_array = convert_env_list(shell->env_list);
	execve(path, cmd->argv, env_array);
	free_str_array(env_array);
	perror("error: execve");
	exit(1);
}

int	exec_parent(pid_t pid, t_minishell *shell)
{
	int	exit_status;

	del();
	waitpid(pid, &shell->last_exit_status, 0);
	if (shell->last_exit_status == 2)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (shell->last_exit_status == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	reset_main();
	if (WIFSIGNALED(shell->last_exit_status))
		exit_status = 128 + WTERMSIG(shell->last_exit_status);
	else
		exit_status = WEXITSTATUS(shell->last_exit_status);
	status_manager(exit_status, STATUS_WRITE);
	return (exit_status);
}

int check_dot(t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], ".") == 0)
	{
		print_error(E_DIR, cmd->argv[0], ERR_SYN);
		ft_putendl_fd(": filename argument required", STDERR_FILENO);
		printf("%s: usage: . filename [arguments]\n", cmd->argv[0]);
		return (1);
	}
	if (ft_strcmp(cmd->argv[0], "..") == 0)
	{
		print_error(E_CMD, cmd->argv[0], ERR_CMD);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int check_slash(t_command *cmd, char **path)
{
	int result;

	if (ft_strchr(cmd->argv[0], '/'))
	{
		result = check_executable_path(cmd->argv[0]);
		if (result != 0)
			return (result);
		*path = ft_strdup(cmd->argv[0]);
		return (0);
	}
	return (-1);
}
