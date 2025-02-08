/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:00:58 by herandri          #+#    #+#             */
/*   Updated: 2024/11/11 11:39:53 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_minishell *shell, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo(shell, args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (cd(shell, args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd(shell, args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (export(shell, args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(shell, args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (env(shell, args));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(shell, args));
	return (-1);
}

int	is_builtin(const char *cmd_name)
{
	static const char *builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
	};
	int	i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd_name, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
