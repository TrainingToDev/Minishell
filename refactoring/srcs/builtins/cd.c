/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:45:41 by herandri          #+#    #+#             */
/*   Updated: 2024/11/27 14:00:12 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_cd(const char *key, t_env_var *env_list)
{
	t_env_var	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static int execute_cd(t_minishell *shell, char *path, int duplicate_path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		shell->last_exit_status = 1;
		if (duplicate_path)
			free(path);
		return (1);
	}
	update_env_pwd(shell);
	if (duplicate_path)
		free(path);

	shell->last_exit_status = 0;
	return (0);
}

static int validate_cd_path(t_minishell *shell, char *path, int duplicate_path)
{
	if (!path || ft_strlen(path) == 0)
	{
		fprintf(stderr, "cd: Invalid path\n");
		shell->last_exit_status = 1;
		if (duplicate_path)
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
	home = NULL;
	if (!args[1])
	{
		home = get_env_cd("HOME", shell->env_list);
		if (!home)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
		}
		path = ft_strdup(home);
		free(home);
		if (!path)
		{
			fprintf(stderr, "cd: Memory allocation failed\n");
			return (NULL);
		}
	}
	else
		path = args[1]; 
	return (path);
}

int	cd(t_minishell *shell, char **args)
{
	char	*path;
	int		duplicate_path;

	duplicate_path = !args[1];
	path = get_cd_path(shell, args);
	if (!path)
		return (1);
	if (validate_cd_path(shell, path, duplicate_path))
		return (1);
	return (execute_cd(shell, path, duplicate_path));
}
