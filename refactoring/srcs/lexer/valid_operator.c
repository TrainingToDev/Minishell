#include "minishell.h"

static int is_operator_invalid_prev(t_token *prev, t_token *current) 
{
	if (!prev || prev->type == TOKEN_PIPE || prev->type == TOKEN_AND 
		|| prev->type == TOKEN_OR || prev->type == TOKEN_LPAREN)
	{
		print_error(E_SYNTAX, current->value, 2);
		return (1);
	}
	return (0);
}

static int is_operator_invalid_next(t_token *current) 
{
	if (!current->next || current->next->type == TOKEN_PIPE || 
		current->next->type == TOKEN_AND || current->next->type == TOKEN_OR
		|| current->next->type == TOKEN_RPAREN)
	{
		print_error(E_SYNTAX, current->value, 2);
		return (1);
	}
	return (0);
}

int	check_operators(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_AND 
			|| tokens->type == TOKEN_OR)
		{
			if (is_operator_invalid_prev(prev, tokens)) 
				return (0);
			if (is_operator_invalid_next(tokens)) 
				return (0);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}
