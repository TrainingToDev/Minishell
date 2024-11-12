/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:59:23 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 11:41:28 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parsing methode for ast, need refactoring and big test with all function

t_ast	*parser(t_token **tokens)
{
	return parse_pipeline(tokens);
}

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left = parse_command(tokens);
	t_ast	*ast;

	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		ast = malloc(sizeof(t_ast));
		if (!ast)
		{
			free_ast(left);
			return (NULL);
		}
		ast->type = NODE_PIPE;
		ast->left = left;
		ast->right = parse_command(tokens);
		left = ast;
	}
	return (left);
}

t_ast	*parse_command(t_token **tokens)
{
	if (*tokens && (*tokens)->type == TOKEN_LPAREN)
		return parse_subshell(tokens);
	else
		return parse_simple_command(tokens);
}

t_ast	*parse_subshell(t_token **tokens)
{
	t_ast	*ast;

	*tokens = (*tokens)->next; // for '('
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->type = NODE_SUBSHELL;
	ast->left = parse_and_or(tokens); // Analyse expression in ()
	if (!ast->left)
	{
		free(ast);
		return (NULL);
	}
	if (!*tokens || (*tokens)->type != TOKEN_RPAREN)
	{
		display_syntax_error("Expected ')'");
		free_ast(ast);
		return (NULL);
	}
	*tokens = (*tokens)->next; // for')'
	ast->right = NULL;
	return (ast);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_command *cmd = malloc(sizeof(t_command));
	t_ast     *ast;

	if (!cmd)
		return (NULL);
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->redirs = NULL;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		add_argument(cmd, (*tokens)->value);
		*tokens = (*tokens)->next;
	}
	while (*tokens && is_redirection_token((*tokens)->type))
	{
		if (!add_redirection(cmd, tokens))
		{
			free_command(cmd);
			return (NULL);
		}
	}
	if (cmd->argc == 0 && cmd->redirs == NULL)
	{
		free_command(cmd);
		return (NULL);
	}
	ast = malloc(sizeof(t_ast));
	if (!ast)
	{
		free_command(cmd);
		return (NULL);
	}
	ast->type = NODE_COMMAND;
	ast->command = cmd;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

t_ast	*parse_input(const char *input)
{
	t_token	*tokens;
	t_ast	*ast;

	tokens = lexer(input);
	if (!tokens)
	{
		display_error("Lexer error: Failed to tokenize input");
		return (NULL);
	}
	if (!validate_tokens(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	ast = parser(&tokens);
	if (!ast)
	{
		display_error("Parser error: Failed to construct AST");
		free_tokens(tokens);
		return (NULL);
	}
	free_tokens(tokens);
	return (ast);
}

t_ast *parse_expression(t_token **tokens)
{
	t_ast	*left;
	t_ast	*ast;

	left = parse_term(tokens);
	while (*tokens && ((*tokens)->type == TOKEN_OR))
	{
		t_token_type	op_type;
		
		op_type = (*tokens)->type;
		*tokens = (*tokens)->next;
		ast = malloc(sizeof(t_ast));
		if (!ast)
		{
			free_ast(left);
			return (NULL);
		}
		ast->type = NODE_LOGICAL;
		ast->operator = op_type;
		ast->left = left;
		ast->right = parse_term(tokens);
		left = ast;
	}
	return (left);
}

t_ast *parse_term(t_token **tokens)
{
	t_ast	*left;
	t_ast	*ast;

	left = parse_factor(tokens);
	while (*tokens && ((*tokens)->type == TOKEN_AND))
	{
		t_token_type op_type;

		op_type = (*tokens)->type;
		*tokens = (*tokens)->next;
		ast = malloc(sizeof(t_ast));
		if (!ast)
		{
			free_ast(left);
			return (NULL);
		}
		ast->type = NODE_LOGICAL;
		ast->operator = op_type;
		ast->left = left;
		ast->right = parse_factor(tokens);
		left = ast;
	}
	return (left);
}

t_ast *parse_factor(t_token **tokens)
{
	t_ast	*ast;
	if ((*tokens)->type == TOKEN_LPAREN)
	{
		*tokens = (*tokens)->next;
		ast = parse_expression(tokens);
		if (!ast || !*tokens || (*tokens)->type != TOKEN_RPAREN)
		{
			display_syntax_error("Expected: ' )'");
			free_ast(ast);
			return (NULL);
		}
		*tokens = (*tokens)->next;
		return (ast);
	}
	else
	{
		return (parse_pipeline(tokens));
	}
}

t_ast	*parse_line(t_token **tokens)
{
	return (parse_and_or(tokens));
}

t_ast	*parse_and_or(t_token **tokens)
{
	t_ast	*left;
	t_ast	*ast;

	left = parse_pipeline(tokens);
	while (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
	{
		t_node_type op_type = (*tokens)->type == TOKEN_AND ? NODE_AND : NODE_OR;
		*tokens = (*tokens)->next;
		ast = malloc(sizeof(t_ast));
		if (!ast)
		{
			free_ast(left);
			return (NULL);
		}
		ast->type = op_type;
		ast->left = left;
		ast->right = parse_pipeline(tokens);
		left = ast;
	}
	return (left);
}
