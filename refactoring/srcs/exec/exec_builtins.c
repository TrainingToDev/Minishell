/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:03:35 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 12:51:03 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int execute_builtin(t_minishell *shell, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return echo(shell, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		return cd(shell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		return pwd(shell, args);
	else if (ft_strcmp(args[0], "export") == 0)
		return export(shell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		return unset(shell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		return env(shell, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		return ft_exit(shell, args);
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
int execute_builtin_cmd(t_command *command, t_minishell *shell)//get_off fork
{
    pid_t	pid;

	if (is_builtin(command->argv[0]))
	{
		return (execute_builtin(shell, command->argv));
	}
	pid = fork();
    if (pid == 0)
	{
        if (apply_redirections(command->redirs, shell) == -1)
		{
            perror("Erreur lors de l'application des redirections");
            exit(1);
        }
        exit(execute_builtin(shell, command->argv));
    }
	else if (pid < 0)
	{
        perror("fork");
        return (1);
    }
    waitpid(pid, &shell->last_exit_status, 0);
    return (WEXITSTATUS(shell->last_exit_status));
}