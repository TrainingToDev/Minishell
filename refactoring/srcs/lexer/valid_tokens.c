#include "minishell.h"

static int check_tokens_validity(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_UNKNOWN)
		{
			print_error(E_SYNTAX, tokens->value, 2);
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}








int validate_syntax(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (!check_operators(tokens))
		return (0);
	if (!check_redirections(tokens))
		return (0);
	if (!check_parentheses(tokens))
		return (0);
	if (!check_tokens_validity(tokens))
		return (0);
	return (1);
}

