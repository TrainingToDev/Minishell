/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:47:39 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 01:18:45 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	free(token);
	token = NULL;
}

void	free_token_list(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free_token(tokens);
		tokens = tmp;
	}
}
