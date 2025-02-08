/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:02:59 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/29 02:03:50 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_key_value(t_env_var *env_var, const char *input_env)
{
	char	*sep;

	if(!input_env)
		return (-1);
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

static t_env_var	*create_env_var(const char *input_env)
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

static void add_env_var(t_env_var **env_list, t_env_var *new_var)
{
	t_env_var *cur;
	
	if (!env_list || !new_var)
		return;
	if (!*env_list)
	{
		*env_list = new_var;
		return ;
	}
	cur = *env_list;
	while (cur->next)
		cur = cur->next;
	cur->next = new_var;
}

t_env_var	*convert_envp_to_list(char **envp)
{
	t_env_var	*env_list;
	t_env_var	*new_var;
	int			i;

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

void	print_env_list(t_env_var *env_list)
{
	t_env_var	*cur;

	cur = env_list;
	while (cur != NULL)
	{
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}
