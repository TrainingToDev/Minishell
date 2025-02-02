/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extern_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:24:57 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/01 23:43:56 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_executable_path(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
	{
		perror(path);
		return (127);
	}
	if (stat(path, &path_stat) == -1)
	{
		perror(path);
		return (126);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (126);
	}
	return (0);
}

static int	prepare_extern_cmd(t_command *cmd, t_minishell *shell, char **path)
{
	int	result;

	if (ft_strcmp(cmd->argv[0], ".") == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", STDERR_FILENO);
		return (127);
	}
	if (ft_strchr(cmd->argv[0], '/'))
	{
		result = check_executable_path(cmd->argv[0]);
		if (result != 0)
			return (result);
		*path = ft_strdup(cmd->argv[0]);
		return (0);
	}
	*path = find_command_path(cmd->argv[0], shell->env_list);
	if (!(*path))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": cmd not found\n", STDERR_FILENO);
		return (127);
	}
	return (0);
}

static int	process_extern(char *path, t_command *cmd, t_minishell *shell)
{
	pid_t	pid;

	setup_child();
	pid = fork();
	if (pid == 0)
	{
		if (apply_redirections(cmd->redirs, shell, 1) == -1)
		{
			perror("Error apply redir");
			exit(1);
		}
		
		execve(path, cmd->argv, convert_env_list(shell->env_list));
		perror("execve");
		exit(1);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	waitpid(pid, &shell->last_exit_status, 0);
	return (WEXITSTATUS(shell->last_exit_status));
}

int	execute_extern_cmd(t_command *cmd, t_minishell *shell)
{
	char	*path;
	int		result;

	result = prepare_extern_cmd(cmd, shell, &path);
	if (result != 0)
		return (result);
	result = process_extern(path, cmd, shell);
	free(path);
	return (result);
}
