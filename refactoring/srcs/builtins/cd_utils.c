/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:15:00 by herandri          #+#    #+#             */
/*   Updated: 2025/01/31 11:40:44 by herandri         ###   ########.fr       */
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

int	update_env_value_if_exists(t_env_var *env_list, const char *key, const char *value)
{
	t_env_var	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
			{
				fprintf(stderr, "Error: Memory allocation failed.\n");
				exit(EXIT_FAILURE);
			}
			return (1);
		}
		current = current->next;
	}
	return (0);
}

t_env_var	*create_new_env_node(const char *key, const char *value)
{
	t_env_var	*new_node;

	new_node = malloc(sizeof(t_env_var));
	if (!new_node)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!new_node->key || !new_node->value)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		exit(EXIT_FAILURE);
	}
	return (new_node);
}

void	append_env_node(t_env_var **env_list, t_env_var *new_node)
{
	t_env_var	*current;

	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	set_env_value(t_env_var **env_list, const char *key, const char *value)
{
	t_env_var	*new_node;

	if (update_env_value_if_exists(*env_list, key, value))
		return ;
	new_node = create_new_env_node(key, value);
	append_env_node(env_list, new_node);
}
