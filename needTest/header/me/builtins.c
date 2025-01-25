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

int execute_builtin(t_minishell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return builtin_echo(shell, cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return builtin_cd(shell, cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return builtin_pwd(shell, NULL);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return builtin_export(shell, cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return builtin_unset(shell, cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return builtin_env(shell, NULL);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return builtin_exit(shell, cmd->argv);
	return (-1);
}

int is_builtin(const char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}
