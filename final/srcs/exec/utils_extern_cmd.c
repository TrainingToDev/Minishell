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

static int check_permissions(char *path, struct stat *path_stat)
{
	if (access(path, F_OK) != 0)
	{
		print_error(E_DIR, path, ERR_CMD);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (ERR_CMD);
	}
	if (stat(path, path_stat) == -1)
	{
		print_error(E_CMD, path, ERR_G);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (126);
	}
	return (0);
}

int check_executable_path(char *path)
{
	struct stat	path_stat;
	int			result;

	result = check_permissions(path, &path_stat);
	if (result != 0)
		return (result);

	if (S_ISDIR(path_stat.st_mode))
    {
        // if (ft_strchr(path, '/'))
        // {
            print_error(E_DIR, path, ERR_DIR);
            ft_putendl_fd(": Is a directory", STDERR_FILENO);
            return (ERR_DIR);
        // }
    }
	if (access(path, X_OK) != 0)
	{
		print_error(E_CMD, path, ERR_DIR);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (ERR_DIR);
	}
	return (0);
}

static int	prepare_extern_cmd(t_command *cmd, t_minishell *shell, char **path)
{
	int	result;
	struct stat path_stat;

	if (ft_strcmp(cmd->argv[0], ".") == 0)
	{
		print_error(E_DIR, cmd->argv[0], ERR_SYN);
		ft_putendl_fd(": filename argument required", STDERR_FILENO);
		printf("%s: usage: . filename [arguments]\n", cmd->argv[0]);
		return (ERR_SYN);
	}
	if (ft_strcmp(cmd->argv[0], "..") == 0)
	{
		print_error(E_CMD, cmd->argv[0], ERR_CMD);
		ft_putendl_fd(": command not found", STDERR_FILENO);
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
	if (stat(cmd->argv[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
    {
        print_error(E_CMD, cmd->argv[0], ERR_CMD);
        ft_putendl_fd(": command not found", STDERR_FILENO);
        return (ERR_CMD);
    }
	*path = find_command_path(cmd->argv[0], shell->env_list);
	if (!(*path))
	{
		print_error(E_CMD, cmd->argv[0], ERR_CMD);
		ft_putendl_fd(": Command not found!!", STDERR_FILENO);
		return (ERR_CMD);
	}
	return (0);
}



static int	process_extern(char *path, t_command *cmd, t_minishell *shell)
{
	pid_t	pid;
	int		f;

	f = 0;
	if (cmd && cmd->argv && cmd->argv[0] != NULL)
		f = 0;
	else
		f = 1;
	if (dir_error(path))
		return (1);
	pid = fork();
	if (pid == 0)
		exec_child(path, cmd, shell, f);
	else if (pid < 0)
	{
		print_error(E_FORK, "fork", ERR_G);
		return (1);
	}
	return (exec_parent(pid, shell));
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
