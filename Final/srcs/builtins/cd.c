/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:45:41 by herandri          #+#    #+#             */
/*   Updated: 2025/01/31 10:16:19 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_pwd(t_minishell *shell)
{
	char	*oldpwd_value;
	char	*newpwd_value;

	if (!shell)
		return ;
	oldpwd_value = get_env_cd("PWD", shell->env_list);
	newpwd_value = getcwd(NULL, 0);
	if (oldpwd_value)
		set_env_value(&shell->env_list, "OLDPWD", oldpwd_value);
	if (newpwd_value)
	{
		set_env_value(&shell->env_list, "PWD", newpwd_value);
		free(newpwd_value);
	}
}

static int	execute_cd(t_minishell *shell, char *path, int dup_path)
{
	if (!path)
	{
		perror("cd: path is NULL");
		return (1);
	}
	if (chdir(path) == -1)
	{
		print_error(E_DIR, "cd", ERR_G);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		if (errno == EACCES)
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
		else if (errno == ENOENT)
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		else if (errno == ENOTDIR)
			ft_putendl_fd(": Not a directory", STDERR_FILENO);
		if (dup_path)
			free(path);
		return (1);
	}
	update_env_pwd(shell);
	if (dup_path)
		free(path);
	status_manager(SUCCESS, STATUS_WRITE);
	return (0);
}

static int	validate_cd_path(char *path, int dup_path)
{
	if (!path || ft_strlen(path) == 0)
	{
		perror("cd: Invalid path");
		if (dup_path)
			free(path);
		return (1);
	}
	return (0);
}

static char	*get_cd_path(t_minishell *shell, char **args)
{
	char	*path;
	char	*home;

	path = NULL;
	if (!args[1])
	{
		home = get_env_cd("HOME", shell->env_list);
		if (!home)
			return (NULL);
		path = ft_strdup(home);
		if (!path)
			return (NULL);
	}
	else
		path = args[1];
	return (path);
}

int	cd(t_minishell *shell, char **args)
{
	char	*path;
	int		dup_path;

	if (!shell || !args)
		return (1);
	if (args[1] && args[2])
	{
		print_error(E_SUP, args[0], ERR_G);
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		return (ERR_G);
	}
	dup_path = !args[1];
	path = get_cd_path(shell, args);
	if (!path)
		return (1);
	if (validate_cd_path(path, dup_path))
		return (1);
	return (execute_cd(shell, path, dup_path));
}
