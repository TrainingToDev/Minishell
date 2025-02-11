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
        print_error(E_DIR, path, ERR_DIR);
        ft_putendl_fd(": Is a directory", STDERR_FILENO);
        return (ERR_DIR);
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
	int	ret;

	ret = check_dot(cmd);
	if (ret != 0)
		return (ret);
	ret = check_slash(cmd, path);
	if (ret != -1)
		return (ret);
	return (find_cmd_path(cmd, shell, path));
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
