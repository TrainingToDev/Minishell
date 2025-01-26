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

int execute_conditional(t_ast *ast, t_minishell *shell)
{
    if (!ast || (ast->type != NODE_AND && ast->type != NODE_OR))
    {
        fprintf(stderr, "execute_conditional: Invalid AST node type\n");
        return (1);
    }
    int left_status = execute_ast(ast->left, shell);
    if (ast->type == NODE_AND)
    {
        if (left_status == 0)
            return (execute_ast(ast->right, shell));
        else
            return left_status;
    }
    else if (ast->type == NODE_OR)
    {
        if (left_status != 0)
            return (execute_ast(ast->right, shell));
        else
            return (left_status);
    }
    fprintf(stderr, "execute_conditional: Unexpected node type\n");
    return (1);
}

pid_t create_subshell_process(t_ast *ast, t_minishell *shell)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }
    else if (pid == 0)
    {
        if (ast->command && ast->command->redirs)
        {
            if (apply_redirections(ast->command->redirs, shell) == -1)
            {
                perror("apply_redirections");
                exit(1);
            }
        }
        if (ast->left)
        {
            int subshell_exit = execute_ast(ast->left, shell);
            exit(subshell_exit);
        }
        exit(0);
    }
    return (pid);
}

int wait_for_subshell(pid_t pid, t_minishell *shell)
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        return (1);
    }
    if (WIFEXITED(status))
        shell->last_exit_status = WEXITSTATUS(status);
    else
        shell->last_exit_status = 1;
    return (shell->last_exit_status);
}

int validate_subshell_node(t_ast *ast)
{
    if (!ast || ast->type != NODE_SUBSHELL)
    {
        fprintf(stderr, "Error: Invalid node type for subshell execution.\n");
        return (0);
    }
    return (1);
}
