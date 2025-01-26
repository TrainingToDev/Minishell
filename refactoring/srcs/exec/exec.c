/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:10:52 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 15:41:37 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int check_cmd(t_command *command)
{
    t_redir	*redir;

    if (!command || !command->argv || command->argc == 0 
		|| ft_strlen(command->argv[0]) == 0)
    {
        redir = command->redirs;
        while (redir)
        {
            if (redir->type == REDIR_IN)
            {
                if (access(redir->filename, F_OK) != 0)
                {
                    ft_putstr_fd("minishell: ", STDERR_FILENO);
                    perror(redir->filename); // No such file or directory
                    return (1);
                }
                return (0);
            }
            redir = redir->next;
        }
        ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
        return (127);
    }
    return (0);
}

static int execute_command(t_command *command, t_minishell *shell)
{
    int result;

    result = check_cmd(command);
    if (result != 0 || (!command || !command->argv 
		|| command->argc == 0))
			return (result);
    if (is_builtin(command->argv[0]))
        return (execute_builtin_cmd(command, shell));
    return (execute_external_cmd(command, shell));
}

static int execute_pipeline(t_ast *ast, t_minishell *shell)
{
	int pipefd[2];
	pid_t pid_left;
	pid_t pid_right;

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
    return (wait_for_children(pid_left, pid_right, shell));
}

int	execute_ast(t_ast *ast, t_minishell *shell)//main principal of exec
{
	if (!ast)
		return (1);
	if (ast->type == NODE_COMMAND)
	{
    	shell->nb_line_heredoc++;
		return (execute_command(ast->command, shell));
	}	
	else if (ast->type == NODE_PIPE)
		return (execute_pipeline(ast, shell));
	else if (ast->type == NODE_AND || ast->type == NODE_OR)
		return (execute_conditional(ast, shell));
	else if (ast->type == NODE_SUBSHELL)
		return (execute_subshell(ast, shell));
	else
		ft_putstr_fd("Erreur : Type de nœud AST inconnu\n", 2);
	return (1);
}
