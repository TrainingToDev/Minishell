/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:21:52 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/05 04:56:21 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*find_pos(t_env_var *env_list, char *key, t_env_var **prev)
{
	t_env_var	*cur;

	cur = env_list;
	*prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur);
		if (ft_strcmp(cur->key, key) > 0)
			break ;
		*prev = cur;
		cur = cur->next;
	}
	return (cur);
}

void	update_env(t_minishell *shell, char *key, char *value)
{
	t_env_var	*cur;
	t_env_var	*prev;
	t_env_var	*new_node;
	char		*new_value;

	cur = find_pos(shell->env_list, key, &prev);
	if (cur && ft_strcmp(cur->key, key) == 0)
	{
		if (value)
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return ;
			free(cur->value);
			cur->value = new_value;
		}
		return ;
	}
	// if (!value)
	// 	value = "";
	new_node = new(key, value, cur);
	if (prev)
		prev->next = new_node;
	else
		shell->env_list = new_node;
}

int	export_arg(t_minishell *shell, char *arg)
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

static int manage_args(t_minishell *shell, char **args, int *valid_args)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (ft_strlen(args[i]) == 0)
		{
			i++;
			continue;
		}
		*valid_args = 1;
		if (export_arg(shell, args[i]) == 1)
			status = 1;
		i++;
	}
	return (status);
}

int	export(t_minishell *shell, char **args)
{
	int	status;
	int	valid_args;

	valid_args = 0;
	if (args[1] && args[1][0] == '-' && args[1][1] != '\0')
	{
		print_error(E_SUP, "export: ", ERR_SYN);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": option not accepted ", STDERR_FILENO);
		return (1);
	}
	if (!args[1])
	{
		display_exported(shell);
		status_manager(SUCCESS, STATUS_WRITE);
		return (0);
	}
	status = manage_args(shell, args, &valid_args);
	if (!valid_args)
	{
		print_error(E_VAR_O, "\n", ERR_G);
		return (1);
	}
	if (status == 0)
		status_manager(SUCCESS, STATUS_WRITE);
	return (status);
}
