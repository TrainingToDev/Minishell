/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexerT.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:18:54 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:57:44 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF,
	TOKEN_UNKNOWN
}   t_token_type;

typedef struct s_token
{
	char            *value;
	t_token_type    type;
	int             expand;
	struct s_token  *next;
}   t_token;


void    display_error(const char *message)
{
	if (!message)
		return ;
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

int is_operator(const char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0 || ft_strncmp(str, "||", 2) == 0 ||
		ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
		return (2);
	else if (*str == '|' || *str == '>' || *str == '<' ||
			 *str == '(' || *str == ')')
		return (1);
	else
		return (0);
}

int is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

t_token_type get_op_token(const char *str)
{
	if (!str)
		return (TOKEN_UNKNOWN);
	if (ft_strncmp(str, "&&", 2) == 0) //for bonus
		return (TOKEN_AND);
	else if (ft_strncmp(str, "||", 2) == 0) //for bonus
		return (TOKEN_OR);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (*str == '>')
		return (TOKEN_REDIRECT_OUT);
	else if (*str == '<')
		return (TOKEN_REDIRECT_IN);
	else if (*str == '|')
		return (TOKEN_PIPE);
	else if (*str == '(') // for bonus
		return (TOKEN_LPAREN);
	else if (*str == ')') // for bonus
		return (TOKEN_RPAREN);
	else
		return (TOKEN_UNKNOWN); // for error
}

t_token *create_token(t_token_type type, const char *value, int expand)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		display_error("Memory allocation error");
		return (NULL);
	}
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		display_error("Memory allocation error");
		return (NULL);
	}
	new_token->expand = expand;
	new_token->next = NULL;
	return (new_token);
}

void add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void add_operator_token(t_token **tokens, const char *input, size_t *i)
{
	int		op_len;
	t_token	*new_token;
	char	*value;

	op_len = is_operator(&input[*i]);
	if (op_len == 0)
	{
		display_error("Invalid operator detected");
		return ;
	}
	value = ft_substr(input, *i, op_len);
	if (!value)
	{
		display_error("Memory allocation error in add_operator_token");
		return ;
	}
	new_token = create_token(get_op_token(&input[*i]), value, 0);
	if (!new_token)
	{
		free(value);
		return ;
	}   
	add_token(tokens, new_token);
	*i += op_len;
}

char *extract_quoted_value(const char *input, size_t *i, int *expand)
{
	char	quote_char;
	size_t	start;
	char	*value;

	quote_char = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (input[*i] != quote_char)
	{
		display_error("Syntax error: Unclosed quote");
		return (NULL);
	}
	*expand = 0;
	if (quote_char == '\"')
		*expand = 1;
	value = ft_substr(input, start, *i - start);
	if (!value)
	{
		display_error("Memory allocation error in extract_quoted_value");
		return (NULL);
	}
	return (value);
}

void add_quoted_token(t_token **tokens, const char *input, size_t *i)
{
	char	*value;
	t_token	*new_token;
	int		expand;

	value = extract_quoted_value(input, i, &expand);
	if (!value)
		return ;
	new_token = create_token(TOKEN_WORD, value, expand);
	free(value);
	if (!new_token)
		return ;
	add_token(tokens, new_token);
	(*i)++;
}

char *extract_word_value(const char *input, size_t *i)
{
	size_t	start;
	char	*value;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) 
			&& !is_operator(&input[*i]) && input[*i] != '\'' 
				&& input[*i] != '\"')
		(*i)++;
	value = ft_substr(input, start, *i - start);
	if (!value)
	{
		display_error("Memory allocation error in extract_word_value");
		return (NULL);
	}
	return (value);
}

void add_word_token(t_token **tokens, const char *input, size_t *i)
{
	char	*value;
	t_token	*new_token;

	value = extract_word_value(input, i);
	if (!value)
		return ;
	new_token = create_token(TOKEN_WORD, value, 1);
	free(value);
	if (!new_token)
		return ;
	add_token(tokens, new_token);
}

void free_tokens(t_token *tokens)
{
    t_token	*temp;

    while (tokens)
    {
        temp = tokens;
        tokens = tokens->next;
        if (temp->value)
            free(temp->value);
        free(temp);
    }
}

t_token *lexer(const char *input)
{
	t_token	*tokens;
	size_t	i;

	if (!input)
		return NULL;
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (is_operator(&input[i]))
			add_operator_token(&tokens, input, &i);
		else if (is_quote(input[i]))
			add_quoted_token(&tokens, input, &i);
		else
			add_word_token(&tokens, input, &i);
	}
	if (!tokens)
    {
        display_error("Lexer error: Failed to add token");
        free_tokens(tokens);
        return NULL;
    }
	return (tokens);
}

// Display the type of token as a string // For testing purposes only
const char *get_token_type_name(t_token_type type)
{
    switch (type)
    {
        case TOKEN_WORD: return "TOKEN_WORD";
        case TOKEN_PIPE: return "TOKEN_PIPE";
        case TOKEN_REDIRECT_IN: return "TOKEN_REDIRECT_IN";
        case TOKEN_REDIRECT_OUT: return "TOKEN_REDIRECT_OUT";
        case TOKEN_APPEND: return "TOKEN_APPEND";
        case TOKEN_HEREDOC: return "TOKEN_HEREDOC";
        case TOKEN_AND: return "TOKEN_AND";
        case TOKEN_OR: return "TOKEN_OR";
        case TOKEN_LPAREN: return "TOKEN_LPAREN";
        case TOKEN_RPAREN: return "TOKEN_RPAREN";
        case TOKEN_EOF: return "TOKEN_EOF";
        case TOKEN_UNKNOWN: return "TOKEN_UNKNOWN";
        default: return "UNKNOWN_TYPE";
    }
}

void print_tokens(t_token *tokens)
{
    t_token *current = tokens;
    while (current)
    {
        printf("Token Type: %s, Value: '%s', Expand: %d\n",
               get_token_type_name(current->type),
               current->value ? current->value : "NULL",
               current->expand);
        current = current->next;
    }
}
// gcc -Wall -Wextra -Werror test_lexerT.c ../libft/libft.a -lreadline
int main(void)
{
    char *input;
    t_token *tokens;

    while (1)
    {
        input = readline("myshell> ");
        if (!input)
            break;
        if (*input)
            add_history(input);
        tokens = lexer(input);
        if (tokens)
        {
            printf("Tokens generated by lexer:\n");
            print_tokens(tokens);
        }
        else
        {
            printf("No tokens generated.\n");
        }
        free_tokens(tokens);
        free(input);
    }
    return 0;
}
