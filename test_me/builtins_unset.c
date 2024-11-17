/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:21:55 by herandri          #+#    #+#             */
/*   Updated: 2024/11/17 11:41:45 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// first implementation for unset

int	is_valid_identifier_unset(const char *str)
{
	int i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_env_var(t_minishell *shell, const char *key)
{
	t_env_var   *current;
	t_env_var   *prev;

	current = shell->env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(t_minishell *shell, char **args)
{
	int i;
	int status = 0;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier_unset(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
			i++;
			continue ;
		}
		remove_env_var(shell, args[i]);
		i++;
	}
	return (status);
}
