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
		fprintf(stderr, "env: No arguments or options allowed\n");
		shell->last_exit_status = 1;
		return (1);
	}
	if (!shell->env_list)
	{
		fprintf(stderr, "env: Environment list is not initialized.\n");
		shell->last_exit_status = 1;
		return (1);
	}
	current = shell->env_list;
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	shell->last_exit_status = 0;
	return (0);
}
