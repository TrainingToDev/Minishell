/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:21:30 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 00:34:41 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*parse_init_pipe(t_parser *parser, char *input)
{
	t_ast	*node_pipe;

	node_pipe = parse_pipe(parser, input);
	if (!node_pipe)
	{
		perror("Invalid pipeline or subshell");
		return (NULL);
	}
	return (node_pipe);
}

static t_ast	*parse_op(t_token_type operator, t_ast *left, t_ast *right)
{
	t_ast	*logic_node;

	if (operator == TOKEN_AND)
		logic_node = create_ast_node(NODE_AND);
	else
		logic_node = create_ast_node(NODE_OR);
	if (!logic_node)
	{
		perror("Failed to create AST node for conditional operator");
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	logic_node->left = left;
	logic_node->right = right;
	return (logic_node);
}

static t_ast	*parse_logic(t_parser *parser, char *input, t_ast *pipe_node)
{
	t_token_type	operator;
	t_ast			*right;
	t_ast			*logic_node;

	while (is_token(parser, TOKEN_AND) || is_token(parser, TOKEN_OR))
	{
		operator = parser->current->type;
		parser_advance(parser);
		right = parse_pipe(parser, input);
		if (!right)
		{
			perror("Invalid pipeline after conditional operator");
			free_ast(pipe_node);
			return (NULL);
		}
		logic_node = parse_op(operator, pipe_node, right);
		if (!logic_node)
			return (NULL);
		pipe_node = logic_node;
	}
	return (pipe_node);
}

t_ast	*parse_list(t_parser *parser, char *input)
{
	t_ast	*pipe_node;

	pipe_node = parse_init_pipe(parser, input);
	if (!pipe_node)
		return (NULL);
	pipe_node = parse_logic(parser, input, pipe_node);
	return (pipe_node);
}
