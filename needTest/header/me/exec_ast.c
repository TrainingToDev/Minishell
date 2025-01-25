/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:12:52 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:28:55 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for logic cmd, need refactoring
int execute_logical(t_minishell *shell, t_ast *ast)
{
    int status_left;

    status_left = execute_ast(shell, ast->left);
    if (ast->type == NODE_AND)
    {
        if (status_left == 0)
            return execute_ast(shell, ast->right);
        else
            return status_left;
    }
    else if (ast->type == NODE_OR)
    {
        if (status_left != 0)
            return execute_ast(shell, ast->right);
        else
            return status_left;
    }
    else
    {
        display_error("Unknown logical operator");
        return (-1);
    }
}
// for bonus, (), need refactoring
int execute_subshell(t_minishell *shell, t_ast *ast)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (-1);
    }
    else if (pid == 0)
    {
        exit(execute_ast(shell, ast->left));
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return (-1);
    }
}
// global execution for ast(arbre syntaxique Abstrait)
int execute_ast(t_minishell *shell, t_ast *ast)
{
    if (!ast)
        return (-1);

    if (ast->type == NODE_COMMAND)
        return execute_command(shell, ast->command);
    else if (ast->type == NODE_PIPE)
        return execute_pipeline(shell, ast);
    else if (ast->type == NODE_AND || ast->type == NODE_OR)
        return execute_logical(shell, ast);
    else if (ast->type == NODE_SUBSHELL)
        return execute_subshell(shell, ast);
    else
    {
        display_error("Unknown AST node type");
        return (-1);
    }
}


