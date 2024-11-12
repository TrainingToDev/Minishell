/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:21:25 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 09:28:06 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// all function is for envp tab to list envp, need big test

void	free_env_var(t_env_var *env_var)
{
	if (env_var)
	{
		free(env_var->key);
		free(env_var->value);
		free(env_var);
	}
}

int	assign_key_value(t_env_var *env_var, const char *input_env)
{
	char	*sep;

	sep = ft_strchr(input_env, '=');
	if (sep)
	{
		env_var->key = ft_substr(input_env, 0, sep - input_env);
		if (!env_var->key)
			return (-1);
		env_var->value = ft_strdup(sep + 1);
		if (!env_var->value)
			return (-1);
	}
	else
	{
		env_var->key = ft_strdup(input_env);
		if (!env_var->key)
			return (-1);
		env_var->value = ft_strdup("");
		if (!env_var->value)
			return (-1);
	}
	return (0);
}

t_env_var	*create_env_var(const char *input_env)
{
	t_env_var	*env_var;

	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	if (assign_key_value(env_var, input_env) == -1)
	{
		free_env_var(env_var);
		return (NULL);
	}
	env_var->next = NULL;
	return (env_var);
}

void add_env_var(t_env_var **env_list, t_env_var *new_var)
{
	t_env_var	*current;

	if (!env_list || !new_var)
		return ;
	new_var->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = new_var;
	}
	else
	{
		current = *env_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_var;
	}
}

t_env_var *convert_envp_to_list(char **envp)
{
	t_env_var   *env_list;
	t_env_var   *new_var;
	int         i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_var = create_env_var(envp[i]);
		if (!new_var)
		{
			free_env_list(env_list);
			return (NULL);
		}
		add_env_var(&env_list, new_var);
		i++;
	}
	return (env_list);
}
