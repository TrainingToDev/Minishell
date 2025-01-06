#include "minishell.h"

static char	*extract_operator_value(char *input, size_t *i, int *op_len)
{
	*op_len = is_operator(&input[*i]);
	if (*op_len == 0)
	{
		print_error(E_SYNTAX, &input[*i], 10);
		return (NULL);
	}
	return (ft_substr(input, *i, *op_len));
}

static void	add_operator_token(t_token **tokens, char *input, size_t *i)
{
	int		op_len;
	char	*value;
	t_token	*new_token;

	value = extract_operator_value(input, i, &op_len);
	if (!value)
		return ;
	new_token = create_token(get_op_token(&input[*i]), value, 0);
	free(value);
	if (!new_token)
		return ;
	add_token(tokens, new_token);
	*i += op_len;
}

static t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	size_t	i;

	if (!input)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		if (ft_isspace(input[i]))
			i++;
		if (invalid_redir(&input[i]) == TOKEN_UNKNOWN)
		{
			free_token_list(tokens);
			return (NULL);
		}
		else if (is_operator(&input[i]))
			add_operator_token(&tokens, input, &i);
		else
			add_word_token(&tokens, input, &i);
		while (input[i] && input[i] != '\n' && ft_isspace(input[i]))
			i++;
	}
	return (tokens);
}

static int	validate_tokens(t_token *tokens)
{
	if (!validate_syntax(tokens))
		return (0);
	if (!tokens)
		return (0);
	return (1);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = tokenize_input(input);
	if (!tokens)
		return (NULL);
	if (!validate_tokens(tokens))
	{
		free_token_list(tokens);
		return (NULL);
	}
	return (tokens);
}
