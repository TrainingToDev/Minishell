/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:47:39 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 10:20:10 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initialization for lexer tokenization
t_token	*create_token(t_token_type type, const char *value, int expand)
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

void	add_token(t_token **tokens, t_token *new_token)
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

void	add_operator_token(t_token **tokens, const char *input, size_t *i)
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

void	add_quoted_token(t_token **tokens, const char *input, size_t *i)
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

void	add_word_token(t_token **tokens, const char *input, size_t *i)
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
