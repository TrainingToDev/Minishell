/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:36:40 by herandri          #+#    #+#             */
/*   Updated: 2025/02/02 17:36:41 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_id(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	sort_array(t_env_var **env_array, int count)
{
	int			i;
	int			j;
	t_env_var	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env_array[i]->key, env_array[j]->key) > 0)
			{
				tmp = env_array[i];
				env_array[i] = env_array[j];
				env_array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int count_vars(t_env_var *env_list)
{
	t_env_var	*current;
	int			count;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_env_var **create_array(t_env_var *env_list, int count)
{
	t_env_var	**env_array;
	t_env_var	*current;
	int			i;

	i = 0;
	current = env_list;
	env_array = malloc(sizeof(t_env_var *) * count);
	if (!env_array)
	{
		perror("malloc");
		return (NULL);
	}
	while (i < count)
	{
		env_array[i] = current;
		current = current->next;
		i++;
	}
	return (env_array);
}

t_env_var	*new(char *key, char *value, t_env_var *current)
{
	t_env_var	*new_node;

	new_node = malloc(sizeof(t_env_var));
	if (!new_node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = current;
	return (new_node);
}
