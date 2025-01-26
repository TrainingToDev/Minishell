#include "minishell.h"

int	is_operator(const char *str)
{
	static const char	*double_operators[] = { 
		"&&", "||", ">>", "<<", ">|", "<>", NULL
	};
	static const char	single_operators[] = "|><()";
	int					i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	while (double_operators[i])
	{
		if (ft_strncmp(str, double_operators[i], 2) == 0)
			return (2);
		i++;
	}
	if (ft_strchr(single_operators, *str))
		return (1);
	return (0);
}

t_token *create_token(t_token_type type, const char *value, int expand)
{
	t_token *new_token;

	if (!value)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		print_error(E_NOMEM, "Memory allocation error", 11);
		return (NULL);
	}
	new_token->type = type;
	new_token->expand = expand;
	new_token->next = NULL;
	return (new_token);
}

t_token_type get_op_token(const char *op)
{
	if (ft_strncmp(op, ">|", 2) == 0)
		return (TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(op, "&&", 2) == 0)
		return (TOKEN_AND);
	else if (ft_strncmp(op, "||", 2) == 0)
		return (TOKEN_OR);
	else if (ft_strncmp(op, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp(op, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (*op == '>')
		return (TOKEN_REDIRECT_OUT);
	else if (*op == '<')
		return (TOKEN_REDIRECT_IN);
	else if (*op == '|')
		return (TOKEN_PIPE);
	else if (*op == '(')
		return (TOKEN_LPAREN);
	else if (*op == ')')
		return (TOKEN_RPAREN);
	else
		return (TOKEN_UNKNOWN);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return ;
	if (new_token->next)
	{
		printf("Token already linked");
		return ;
	}
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

int is_quote(char c)
{
    return (c == '\'' || c == '\"');
}
