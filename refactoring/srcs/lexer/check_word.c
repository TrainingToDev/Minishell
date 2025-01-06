#include "minishell.h"

static char	*join_and_free(char *value, char *part)
{
	char	*tmp;

	tmp = ft_strjoin(value, part);
	free(value);
	free(part);
	if (!tmp)
		print_error(E_NOMEM, NULL, 11);
	return (tmp);
}

static char	*extract_part(char *input, size_t *i)
{
	size_t	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
			&& !is_operator(&input[*i])
				&& !is_quote(input[*i]))
					(*i)++;
	return (ft_substr(input, start, *i - start));
}

static char	*quoted_part(char *input, size_t *i, int *expand, char *value)
{
	char	*part;
	char	*tmp;
	int		part_expand;

	part = extract_quoted_value(input, i, &part_expand);
	if (!part)
	{
		free(value);
		return (NULL);
	}
	if (part_expand)
		*expand = 1;
	tmp = join_and_free(value, part);
	return (tmp);
}

static char	*process_input(char *input, size_t *i, int *expand, char *value)
{
	char	*part;

	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(&input[*i]))
	{
		if (is_quote(input[*i]))
		{
			value = quoted_part(input, i, expand, value);
			if (!value)
				return (NULL);
		}
		else
		{
			part = extract_part(input, i);
			if (!part)
			{
				free(value);
				print_error(E_NOMEM, NULL, 11);
				return (NULL);
			}
			value = join_and_free(value, part);
			if (!value)
				return (NULL);
		}
	}
	return (value);
}

char	*extract_word_value(char *input, size_t *i, int *expand)
{
	char	*value;

	if (!input || !i || !expand)
		return (NULL);
	value = ft_strdup("");
	if (!value)
	{
		print_error(E_NOMEM, NULL, 11);
		return (NULL);
	}
	value = process_input(input, i, expand, value);
	if (!value)
		free(value);
	return (value);
}
