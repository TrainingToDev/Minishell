#include "minishell.h"

//bonus

static int process_substitution(t_token *token)
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

static int process_parenthesis(t_token *token, int *count)
{
    if (!process_substitution(token))
        return (0);

    if (token->type == TOKEN_LPAREN)
    {
        (*count)++;
        if (token->next && token->next->type == TOKEN_RPAREN)
        {
            print_error(E_SYNTAX, ")", 258);
            return (0);
        }
    }
    else if (token->type == TOKEN_RPAREN)
    {
        (*count)--;
        if (*count < 0)
        {
            print_error(E_SYNTAX, ")", 258);
            return (0);
        }
    }
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
    return (1);
}

