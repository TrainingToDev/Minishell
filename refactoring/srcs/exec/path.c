/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:54:23 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/01 23:43:21 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(const char *key, t_env_var *env_list)
{
	t_env_var	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

static char	*get_path(char **path, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin_free(ft_strjoin(path[i], "/"), cmd, 1);
		if (!full_path)
		{
			free_str_array(path);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_str_array(path);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_str_array(path);
	return (NULL);
}

char	*find_command_path(char *cmd_name, t_env_var *env_list)
{
	char	**paths;
	char	*path_env;

	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	path_env = get_env_value("PATH", env_list);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	return (get_path(paths, cmd_name));
}

void	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
