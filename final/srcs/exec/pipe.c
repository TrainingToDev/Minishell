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
	int		exit_status;

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
			exit_status = execute_command(ast->command, shell, 1);
		else
			exit_status = execute_ast(ast, shell);
		status_manager(exit_status, STATUS_WRITE);//
		exit(exit_status);
	}
	return (pid);
}

pid_t	fork_and_exec_right(t_ast *ast, int pipefd[2], t_minishell *shell)
{
	pid_t	pid;
	int		exit_status;

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
			exit_status = execute_command(ast->command, shell, 1);
		else
			exit_status = execute_ast(ast, shell);
		status_manager(exit_status, STATUS_WRITE);//
		exit(exit_status);
	}
	return (pid);
}

int	wait_for_children(pid_t pid_left, pid_t pid_right)
{
	int	status_left;
	int	status_right;
	int exit_status;

	exit_status = 0;
	status_left = 0;
	status_right = 0;
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFEXITED(status_right))
		exit_status = WEXITSTATUS(status_right);
	else if (WIFSIGNALED(status_right))
		exit_status = 128 + WTERMSIG(status_right);
	status_manager(exit_status, STATUS_WRITE);
	return (exit_status);
}
