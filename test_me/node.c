/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 02:01:33 by herandri          #+#    #+#             */
/*   Updated: 2024/11/23 11:16:45 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_ast_node(t_node_type type, t_command *cmd)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		display_error("Memory allocation failed for AST node");
		return	(NULL);
	}
	node->type = type;
	node->command = cmd;
	node->operator = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
    t_ast	*node;

	node = create_ast_node(NODE_PIPE, NULL);
    if (!node)
        return (NULL);
    node->left = left;
    node->right = right;
    return (node);
}

t_ast	*create_logical_node(t_node_type type, t_ast *left, t_ast *right)
{
    t_ast	*node;

	node = create_ast_node(type, NULL);
    if (!node)
		return (NULL);
    node->left = left;
    node->right = right;
    return (node);
}

// apply one function 
void traverse_ast(t_ast *node, void (*callback)(t_ast *))
{
    if (!node)
        return ;
    callback(node);
    if (node->left)
        traverse_ast(node->left, callback);
    if (node->right)
        traverse_ast(node->right, callback);
}

//test for execution
int evaluate_ast(t_ast *node)
{
    if (!node)
        return (0);

    if (node->type == NODE_COMMAND)
        return (execute_command(node->command));

    if (node->type == NODE_PIPE)
        return (execute_pipe(node->left, node->right));

    if (node->type == NODE_AND)
    {
        int left_result = evaluate_ast(node->left);
        if (left_result != 0)
            return (0);
        return (evaluate_ast(node->right));
    }

    if (node->type == NODE_OR)
    {
        int left_result = evaluate_ast(node->left);
        if (left_result == 0)
            return (0);
        return (evaluate_ast(node->right));
    }

    if (node->type == NODE_SUBSHELL)
        return (execute_subshell(node->left));
    display_error("Unknown AST node type");
    return (-1);
}

//test for parsing
int validate_ast(t_ast *node)
{
    if (!node)
        return (1);
    if (node->type == NODE_PIPE)
    {
        if (!node->left || !node->right)
        {
            display_error("Invalid AST: PIPE node");
            return (0);
        }
    }
    if (node->type == NODE_COMMAND)
    {
        if (!node->command || node->command->argc == 0)
        {
            display_error("Invalid AST: COMMAND node must have arguments");
            return (0);
        }
    }
    if (!validate_ast(node->left) || !validate_ast(node->right))
        return (0);
    return (1);
}
// need redactoring
t_command	*copy_command(t_command *cmd)
{
    t_command		*copy;
    t_redirection	*current_redir;
    t_redirection	*new_redir;

    if (!cmd)
        return (NULL);
    copy = init_command();
    if (!copy)
        return (NULL);
    int i = 0;
    while (i < cmd->argc)
    {
        if (!add_argument(copy, cmd->argv[i]))
        {
            free_command(copy);
            return (NULL);
        }
        i++;
    }
    current_redir = cmd->redirs;
    while (current_redir)
    {
        new_redir = malloc(sizeof(t_redirection));
        if (!new_redir)
        {
            free_command(copy);
            return (NULL);
        }
        new_redir->type = current_redir->type;
        new_redir->filename = ft_strdup(current_redir->filename);
        if (!new_redir->filename)
        {
            free(new_redir);
            free_command(copy);
            return (NULL);
        }
        new_redir->next = NULL;

        if (!copy->redirs)
            copy->redirs = new_redir;
        else
        {
            t_redirection *tmp = copy->redirs;
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = new_redir;
        }
        current_redir = current_redir->next;
    }
    return (copy);
}

t_ast *copy_ast_node(t_ast *node)
{
    t_ast	*copy;

    if (!node)
        return (NULL);
    if (node->command)
        copy = create_ast_node(node->type, copy_command(node->command));
    else
        copy = create_ast_node(node->type, NULL);
    if (!copy)
        return (NULL);
    if (node->left)
        copy->left = copy_ast_node(node->left);
    if (node->right)
        copy->right = copy_ast_node(node->right);
    return (copy);
}

