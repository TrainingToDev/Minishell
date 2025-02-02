/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:21:52 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/02 16:08:46 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_exporded(t_minishell *shell)
{
	int			count;
	t_env_var	**env_array;

	count = count_vars(shell->env_list);
	if (count == 0)
		return ;
	env_array = create_array(shell->env_list, count);
	if (!env_array)
		return ;
	sort_array(env_array, count);
	display_env(env_array, count);
	free(env_array);
}

static t_env_var	*find_position(t_env_var *env_list, char *key, t_env_var **previous)
{
	t_env_var	*current;

	current = env_list;
	*previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		if (ft_strcmp(current->key, key) > 0)
			break ;
		*previous = current;
		current = current->next;
	}
	return (current);
}

static void	update_env(t_minishell *shell, char *key, char *value)
{
	t_env_var	*current;
	t_env_var	*previous;
	t_env_var	*new_node;

	current = find_position(shell->env_list, key, &previous);
	if (current && ft_strcmp(current->key, key) == 0)
	{
		free(current->value);
		if (value)
			current->value = ft_strdup(value);
		else
			current->value = NULL;
		return ;
	}
	new_node = new(key, value, current);
	if (previous)
		previous->next = new_node;
	else
		shell->env_list = new_node;
}

static int	export_arg(t_minishell *shell, char *arg)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (!is_valid_id(key))
	{
		free(key);
		free(value);
		return (export_error(arg));
	}
	update_env(shell, key, value);
	free(key);
	free(value);
	return (0);
}

int	export(t_minishell *shell, char **args)
{
	int	i;
	int	status;

	if (!args[1])
	{
		display_exporded(shell);
		return (0);
	}
	status = 0;
	i = 1;
	while (args[i])
	{
		if (export_arg(shell, args[i]) == 1)
			status = 1;
		i++;
	}
	return (status);
}
