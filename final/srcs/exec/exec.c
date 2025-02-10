/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:10:52 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/02 15:10:41 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd(t_command *cmd)
{
	if (!cmd || (!cmd->argv && !cmd->redirs))
	{
		print_error(E_SUP, "Parsing failed!!!\n", ERR_SYN);
		return (ERR_SYN);
	}
	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (0);
	return (1);
}

int	execute_command(t_command *command, t_minishell *shell, int fork_required)
{
	int	result;

	result = check_cmd(command);
	if (result == ERR_SYN)
		return ERR_SYN;
	if (result == 0)
	{
		if (command && command->redirs)
			return (apply_redir(command->redirs, shell, 0, 1));
		return (0);
	}
	if (is_builtin(command->argv[0]))
	{
		// printf("builTIN\n");
		return (execute_builtin_cmd(command, shell, fork_required));
	}
	// printf("EXEC_EXTERN\n");
	return (execute_extern_cmd(command, shell));
}

static int	execute_pipeline(t_ast *ast, t_minishell *shell)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (!ast || ast->type != NODE_PIPE)
		return (execute_ast(ast, shell));
	if (init_pipe(pipefd) != 0)
		return (1);
	pid_left = fork_and_exec_left(ast->left, pipefd, shell);
	if (pid_left < 0)
	{
		close_pipe_descriptors(pipefd);
		return (1);
	}
	pid_right = fork_and_exec_right(ast->right, pipefd, shell);
	if (pid_right < 0)
	{
		close_pipe_descriptors(pipefd);
		return (1);
	}
	close_pipe_descriptors(pipefd);
	return (wait_for_children(pid_left, pid_right));
}


// static int execute_pipeline(t_ast *ast, t_minishell *shell)
// {
// 	int pipefd[2];
// 	pid_t pid;

// 	if (!ast || ast->type != NODE_PIPE)
// 		return (execute_ast(ast, shell));
// 	if (pipe(pipefd) == -1)
// 		return (1);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		close_pipe_descriptors(pipefd);
// 		return (1);
// 	}
// 	if (pid == 0)
// 	{
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		close_pipe_descriptors(pipefd);
// 		exit(execute_ast(ast->left, shell));
// 	}
// 	close(pipefd[1]);
// 	dup2(pipefd[0], STDIN_FILENO);
// 	close(pipefd[0]);
// 	return (execute_ast(ast->right, shell));
// }

int	execute_ast(t_ast *ast, t_minishell *shell)
{
	int	exit_status;

	if (!ast)
		return (1);
	if (ast->type == NODE_COMMAND)
	{
		shell->nb_line_heredoc++;
		exit_status = execute_command(ast->command, shell, 0);
	}
	else if (ast->type == NODE_PIPE)
		exit_status = execute_pipeline(ast, shell);
	else if (ast->type == NODE_AND || ast->type == NODE_OR)
		exit_status = execute_conditional(ast, shell);
	else if (ast->type == NODE_SUBSHELL)
		exit_status = execute_subshell(ast, shell);
	else
	{
		ft_putstr_fd("Erreur : Type de nœud AST inconnu\n", 2);
		exit_status = 1;
	}
	// status_manager(exit_status, STATUS_WRITE);
	return (exit_status);
}
