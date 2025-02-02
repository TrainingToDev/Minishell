/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:08:58 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 15:25:11 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe(int pipefd[2])
{
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

void	close_pipe_descriptors(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

pid_t fork_and_exec_left(t_ast *ast, int pipefd[2], t_minishell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close_pipe_descriptors(pipefd);
		if (ast->type == NODE_COMMAND)
			exit(execute_command(ast->command, shell, 1));
		else
			exit(execute_ast(ast, shell));
	}
	return (pid);
}

pid_t	fork_and_exec_right(t_ast *ast, int pipefd[2], t_minishell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close_pipe_descriptors(pipefd);
		if (ast->type == NODE_COMMAND)
			exit(execute_command(ast->command, shell, 1));
		else
			exit(execute_ast(ast, shell));
	}
	return (pid);
}

int	wait_for_children(pid_t pid_left, pid_t pid_right, t_minishell *shell)
{
	int	status_left;
	int	status_right;

	status_left = 0;
	status_right = 0;
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFEXITED(status_right))
		shell->last_exit_status = WEXITSTATUS(status_right);
	else
		shell->last_exit_status = 1;
	return (shell->last_exit_status);
}
