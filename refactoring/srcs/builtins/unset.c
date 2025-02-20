/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:52 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/26 00:01:33 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_id_unset(const char *str)
{
	int	i;

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
	t_env_var	*current;
	t_env_var	*prev;

	if (!shell || !key)
		return ;
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

int	unset(t_minishell *shell, char **args)
{
	int	i;

	if (!shell || !args)
		return (1);
	if (args[1] && args[1][0] == '-' && args[1][1] != '\0')
	{
		print_error(E_SUP, "unset: ", ERR_SYN);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": option not accepted", STDERR_FILENO);
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_id_unset(args[i]))
		{
			i++;
			continue ;
		}
		remove_env_var(shell, args[i]);
		i++;
	}
	status_manager(SUCCESS, STATUS_WRITE);
	return (0);
}
