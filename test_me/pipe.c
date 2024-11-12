/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:57:47 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:25:26 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// first implemation for pipe, need refactoring
int execute_pipeline(t_minishell *shell, t_ast *ast)
{
	int     pipe_fd[2];
	pid_t   pid;
	int     status = 0;

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		// Processus enfant : exécute la commande de gauche
		close(pipe_fd[0]); // Ferme la lecture du pipe
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(execute_ast(shell, ast->left));
	}
	else
	{
		// Processus parent : exécute la commande de droite
		close(pipe_fd[1]); // Ferme l'écriture du pipe
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		status = execute_ast(shell, ast->right);
		waitpid(pid, NULL, 0);
	}
	return (status);
}
