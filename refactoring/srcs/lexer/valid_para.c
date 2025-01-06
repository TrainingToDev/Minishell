#include "minishell.h"

int	check_parentheses(t_token *tokens)
{
	int	count;

    count = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_LPAREN)
			count++;
		else if (tokens->type == TOKEN_RPAREN)
		{
			count--;
			if (count < 0)
			{
				print_error(E_SYNTAX, tokens->value, 258);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	if (count != 0)
	{
		print_error(E_SYNTAX, "unmatched parenthesis", 258);
		return (0);
	}
	return (1);
}
