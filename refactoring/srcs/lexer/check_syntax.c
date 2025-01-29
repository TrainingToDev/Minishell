/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:47:39 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 01:18:49 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_tokens_validity(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_UNKNOWN)
		{
			print_error(E_SYNTAX, tokens->value, 2);
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	validate_syntax(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (!check_operators(tokens))
		return (0);
	if (!check_redirections(tokens))
		return (0);
	if (!check_parentheses(tokens))
		return (0);
	if (!check_tokens_validity(tokens))
		return (0);
	return (1);
}
