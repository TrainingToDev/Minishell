/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:15:29 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/26 00:03:51 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_minishell *shell, char **args)
{
	t_env_var	*current;

	current = NULL;
	if (args[1])
	{
		print_error(E_SUP, "env: No arguments or options allowed\n", ERR_SYN);
		return (1);
	}
	if (!shell->env_list)
	{
		perror("env: not initialized.\n");
		return (1);
	}
	current = shell->env_list;
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	status_manager(SUCCESS, STATUS_WRITE);
	return (0);
}
