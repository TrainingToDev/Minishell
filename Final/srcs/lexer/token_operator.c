/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:48:29 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 01:19:22 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_operator_value(char *input, size_t *i, int *op_len)
{
	if (!input || !i || !op_len)
		return (NULL);
	*op_len = is_operator(&input[*i]);
	if (*op_len == 0)
		return (NULL);
	return (ft_substr(input, *i, *op_len));
}

void	add_operator_token(t_token **tokens, char *input, size_t *i)
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
		print_error(E_QUOTE, "Unclosed quote\n", ERR_SYN);
		return (NULL);
	}
	value = ft_substr(input, start, (*i) - start + 1);
	if (!value)
		return (NULL);
	(*i)++;
	return (value);
}
