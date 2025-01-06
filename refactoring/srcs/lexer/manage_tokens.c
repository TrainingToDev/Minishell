#include "minishell.h"

char	*extract_quoted_value(char *input, size_t *i, int *expand)
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
