/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:05:31 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:46:40 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for all function need refactoring

char *find_executable(const char *cmd, t_minishell *shell)
{
	char    **paths;
	char    *full_path;
	int     i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(get_env_value(shell->env_list, "PATH"), ':');
	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin_three(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_string_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_string_array(paths);
	return (NULL);
}

int update_env(t_minishell *shell, const char *key, const char *value)
{
    t_env_var *current = shell->env_list;


    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            if (!current->value)
            {
                perror("update_env");
                return (1);
            }
            return (0);
        }
        current = current->next;
    }
    // if var not exit, added
    t_env_var *new_var = malloc(sizeof(t_env_var));
    if (!new_var)
    {
        perror("update_env");
        return (1);
    }
    new_var->key = ft_strdup(key);
    new_var->value = ft_strdup(value);
    if (!new_var->key || !new_var->value)
    {
        perror("update_env");
        free(new_var->key);
        free(new_var->value);
        free(new_var);
        return (1);
    }
    new_var->next = shell->env_list;
    shell->env_list = new_var;
    return (0);
}