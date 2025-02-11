/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:47:39 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 01:19:02 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_logical_op(t_token_type type)
{
	return (type == TOKEN_AND || type == TOKEN_OR);
}

static int	is_pipe_op(t_token_type type)
{
	return (type == TOKEN_PIPE);
}

static int	validate_operator(t_token *prev, t_token *current)
{
	if (is_pipe_op(current->type) || is_logical_op(current->type))
	{
		if (!prev || prev->type == TOKEN_PIPE || prev->type == TOKEN_AND
			|| prev->type == TOKEN_OR || prev->type == TOKEN_LPAREN)
		{
			print_error(E_SYNTAX, current->value, ERR_SYN);
			return (0);
		}
		if (!current->next || current->next->type == TOKEN_PIPE
			|| current->next->type == TOKEN_AND
			|| current->next->type == TOKEN_OR
			|| current->next->type == TOKEN_RPAREN)
		{
			print_error(E_SYNTAX, current->value, ERR_SYN);
			return (0);
		}
	}
	return (1);
}

int	check_operators(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (!validate_operator(prev, tokens))
			return (0);
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}
