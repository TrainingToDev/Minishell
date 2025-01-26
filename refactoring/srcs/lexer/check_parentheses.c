#include "minishell.h"

static int open_parenthesis(t_token *token, int *count)
{
    (*count)++;
    if (token->next && token->next->type == TOKEN_RPAREN)
    {
        print_error(E_SYNTAX, ")", 258);
        return (0);
    }
    return (1);
}

static int close_parenthesis(t_token *token, int *count)
{
    (*count)--;
    if (token->next && token->next->type == TOKEN_LPAREN)
    {
        print_error(E_SYNTAX, "(", 258);
        return (0);
    }
    if (*count < 0)
    {
        print_error(E_SYNTAX, ")", 258);
        return (0);
    }
    return (1);
}


static int process_parenthesis(t_token *token, int *count)
{
    if (!process_substitution(token))
        return (0);

    if (token->type == TOKEN_LPAREN)
        return open_parenthesis(token, count);

    if (token->type == TOKEN_RPAREN)
        return close_parenthesis(token, count);

    return (1);
}


static int validate_parenthesis_count(t_token *tokens, int *count)
{
	while (tokens)
	{
		if (!process_parenthesis(tokens, count))
			return (0);
		tokens = tokens->next;
	}
	if (*count != 0)
	{
		print_error(E_SYNTAX, "unmatched parenthesis", 258);
		return (0);
	}
	return (1);
}

int check_parentheses(t_token *tokens)
{
	int count;

	count = 0;
	if (!validate_parenthesis_count(tokens, &count))
		return (0);
	 if (is_disallowed(tokens))
        return (0);
	return (1);
}
