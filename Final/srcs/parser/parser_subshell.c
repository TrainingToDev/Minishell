/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:21:30 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 00:40:04 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	subshell_syntax(t_parser *parser, t_ast **subshell, char *input)
{
	if (!is_token(parser, TOKEN_LPAREN))
		return (-1);
	parser_advance(parser);
	if (is_token(parser, TOKEN_RPAREN))
	{
		print_error(E_SYNTAX, parser->current->value, ERR_SYN);
		return (-1);
	}
	*subshell = parse_list(parser, input);
	if (!(*subshell))
	{
		print_error(E_SYNTAX, parser->current->value, ERR_SYN);
		return (-1);
	}
	if (!is_token(parser, TOKEN_RPAREN))
	{
		print_error(E_SYNTAX, parser->current->value, ERR_SYN);
		free_ast(*subshell);
		return (-1);
	}
	parser_advance(parser);
	return (0);
}

t_ast	*parse_subshell(t_parser *parser, char *input)
{
	t_ast	*subshell;

	subshell = NULL;
	if (subshell_syntax(parser, &subshell, input) == -1)
		return (NULL);
	if (is_token(parser, TOKEN_WORD)
		|| is_token(parser, TOKEN_LPAREN))
	{
		print_error(E_SYNTAX, parser->current->value, ERR_SYN);
		free_ast(subshell);
		return (NULL);
	}
	return (subshell);
}
