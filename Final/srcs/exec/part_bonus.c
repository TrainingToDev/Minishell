/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:28:01 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 15:54:48 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_subshell_node(t_ast *ast)
{
	if (!ast || ast->type != NODE_SUBSHELL)
	{
		perror("Error: Invalid node type for subshell execution.\n");
		return (0);
	}
	return (1);
}

static pid_t	create_subshell_process(t_ast *ast, t_minishell *shell)
{
	pid_t	pid;
	int		subshell_exit;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (ast->command && ast->command->redirs)
		{
			if (redirections(ast->command->redirs, shell) == -1)
				exit(1);
		}
		if (ast->left)
		{
			subshell_exit = execute_ast(ast->left, shell);
			exit(subshell_exit);
		}
		exit(0);
	}
	return (pid);
}

static int	wait_for_subshell(pid_t pid)
{
	int	status;
	int	exit_status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	else
		exit_status = 1;
	status_manager(exit_status, STATUS_WRITE);
	return (exit_status);
}

int	execute_subshell(t_ast *ast, t_minishell *shell)
{
	pid_t	pid;

	if (!validate_subshell_node(ast))
		return (1);
	pid = create_subshell_process(ast, shell);
	if (pid == -1)
		return (1);
	return (wait_for_subshell(pid));
}

int	execute_conditional(t_ast *ast, t_minishell *shell)
{
	int	exit_left;
	int	exit_right;
	int	exit_status;

	if (!ast || (ast->type != NODE_AND && ast->type != NODE_OR))
	{
		printf("execute_conditional: Invalid AST node type\n");
		return (1);
	}
	exit_right = -1;
	exit_left = execute_ast(ast->left, shell);
	status_manager(exit_left, STATUS_WRITE);
	if (ast->type == NODE_AND && exit_left == 0)
		exit_right = execute_ast(ast->right, shell);
	else if (ast->type == NODE_OR && exit_left != 0)
		exit_right = execute_ast(ast->right, shell);
	if (exit_right != -1)
	{
		status_manager(exit_right, STATUS_WRITE);
		exit_status = exit_right;
	}
	else
		exit_status = exit_left;
	return (exit_status);
}
