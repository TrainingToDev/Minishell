#include "minishell.h"

static char *extract_operator_value(char *input, size_t *i, int *op_len)
{
	if (!input || !i || !op_len)
		return (NULL);
	*op_len = is_operator(&input[*i]);
	if (*op_len == 0)
	{
		print_error(E_SYNTAX, &input[*i], 10);
		return (NULL);

	}
	return ft_substr(input, *i, *op_len);
}

void add_operator_token(t_token **tokens, char *input, size_t *i)
{
	int     op_len;
	char    *value;
	t_token *new_token;

	value = extract_operator_value(input, i, &op_len);
	if (!value)
		return ;
	new_token = create_token(get_op_token(&input[*i]), value, 0);
	free(value);
	if (!new_token)
		return ; //msg
	add_token(tokens, new_token);
	*i += op_len;
}

char *extract_quoted_value(char *input, size_t *i, int *expand)
{
	size_t	start;
	char	*value;

	if (!input || !i || !expand)
		return (NULL);
	*expand = (input[*i] == '\"');
	start = (*i)++;
	while (input[*i] && input[*i] != input[start])
		(*i)++;
	if (!input[*i])
	{
		print_error(E_QUOTE, NULL, 1);
		return (NULL);
	}
	value = ft_substr(input, start, (*i) - start + 1);
	if (!value)
		return (NULL);
	(*i)++;
	return (value);
}