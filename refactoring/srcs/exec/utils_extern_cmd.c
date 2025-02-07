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

	if (access(path, F_OK) != 0) //path inexist dir
	{
		printf("{here1}\n");
		print_error(E_DIR, path, ERR_G);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (ERR_G);
	}
	if (stat(path, &path_stat) == -1)
	{
		printf("{here2}\n");
		print_error(E_CMD, path, ERR_G);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (126);
	}
	if (S_ISDIR(path_stat.st_mode)) // dir exist
	{
		printf("{here3}\n");
		print_error(E_DIR, path, ERR_DIR);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		return (ERR_DIR);
	}
	if (access(path, X_OK) != 0) // permission
	{
		printf("{here4}\n");
		print_error(E_CMD, path, ERR_DIR);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (ERR_DIR);
	}
	return (0);
}

static int	prepare_extern_cmd(t_command *cmd, t_minishell *shell, char **path)
{
	int	result;

	if (ft_strcmp(cmd->argv[0], ".") == 0) // test .
	{
		print_error(E_DIR, cmd->argv[0], ERR_SYN);
		ft_putendl_fd(": filename argument required", STDERR_FILENO);
		printf("%s: usage: . filename [arguments]\n", cmd->argv[0]);
		return (ERR_SYN);
	}
	if (ft_strcmp(cmd->argv[0], "..") == 0)
	{
		printf("cmd-1\n");
		print_error(E_CMD, cmd->argv[0], ERR_CMD);
		ft_putendl_fd(": Command not found", STDERR_FILENO);
		return (ERR_CMD);
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
		printf("cmd-2\n");
		print_error(E_CMD, cmd->argv[0], ERR_CMD);
		ft_putendl_fd(": Command not found!!", STDERR_FILENO);
		return (ERR_CMD);
	}
	return (0);
}

static int	process_extern(char *path, t_command *cmd, t_minishell *shell)
{
	pid_t	pid;
	char **env_array;
	int exit_status;

	pid = fork();
	if (pid == 0)
	{
		setup_child();//signal
		printf("io1\n");
		if (apply_redirections(cmd->redirs, shell, 1) == -1)
		{
			printf("REDIR>>>-1\n");
			print_error(E_DIR,cmd->redirs->filename, ERR_G);
			ft_putendl_fd(": No such file or directory!!!", STDERR_FILENO);
			return (1);
		}
		printf("eto\n");
		env_array = convert_env_list(shell->env_list);
		printf("eto->>>>\n");
		execve(path, cmd->argv, env_array);
		printf("eto oa!!!\n");
		free_str_array(env_array);
		perror("error: execve");
		printf("iof2\n");
		exit(1);
	}
	else if (pid < 0)
	{
		print_error(E_FORK, "fork", ERR_G);
		return (1);
	}
	waitpid(pid, &shell->last_exit_status, 0);
	if (WIFSIGNALED(shell->last_exit_status))
		exit_status = 128 + WTERMSIG(shell->last_exit_status);
	else
		exit_status = WEXITSTATUS(shell->last_exit_status);
	status_manager(exit_status, STATUS_WRITE);
	return (exit_status);
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
