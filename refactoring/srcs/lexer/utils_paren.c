#include "minishell.h"

static t_token *find_matching_rparen(t_token *start)
{
    t_token *it;

	it = start;
    while (it)
    {
        if (it->type == TOKEN_RPAREN)
            return (it);
        it = it->next;
    }
    return (NULL);
}

static t_token *get_disallowed(t_token *tokens)
{
    t_token *cur;
    t_token *closing;
    t_token *next_token;

    cur = tokens;
    while (cur)
    {
        if (cur->type == TOKEN_LPAREN)
        {
            closing = find_matching_rparen(cur->next);
            if (closing)
            {
                next_token = closing->next;
                if (next_token && next_token->type == TOKEN_WORD)
                {
                    return (next_token); 
                }
            }
        }
        cur = cur->next;
    }
    return (NULL);
}

int is_disallowed(t_token *tokens)
{
    t_token	*bad_token;

	bad_token = get_disallowed(tokens);
    if (bad_token)
    {
        print_error(E_SYNTAX, bad_token->value, 2);
        return (1);
    }
    return (0);
}

int process_substitution(t_token *token)
{
	if (token->type == TOKEN_WORD && token->value && 
		token->value[0] == '$' && token->next && token->next->type == TOKEN_LPAREN)
	{
		if (token->next->next && token->next->next->type == TOKEN_WORD)
		{
			print_error(E_SYNTAX, "substitution not supported", 258);
			return (0);
		}
	}
	return (1);
}
