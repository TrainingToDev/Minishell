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

#include "minishell.h"

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
