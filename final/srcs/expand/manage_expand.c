/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:03:35 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/05 04:54:14 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_expand(t_token *token, t_token *tokens, t_minishell *shell)
{
	char	*expanded;

	if (token->type == TOKEN_WORD)
	{
		if (token->expand == 0)
			return (1);
		if (ft_strchr(token->value, '$') && !is_single_quoted(token->value))
		{
			expanded = expand_var(token->value, shell);
			if (!expanded)
			{
				perror("Memory allocation failed\n");
				free_token_list(tokens);
				shell->running = 0;
				return (0);
			}
			free(token->value);
			token->value = expanded;
		}
	}
	return (1);
}

void	expand_token_list(t_token *tokens, t_minishell *shell)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (!token_expand(current, tokens, shell))
			return ;
		current = current->next;
	}
}

char	*scan_token(char *src, t_state *s, char *res, t_minishell *shell)
{
	if (src[s->index] == '\'')
	{
		s->single_quote = !s->single_quote;
		s->index++;
	}
	else if (src[s->index] == '$' && !s->single_quote)
	{
		res = proc_dlr(src, &s->index, res, shell);
		if (!res)
			return (NULL);
	}
	else
	{
		res = add_char(src, &s->index, res);
		if (!res)
			return (NULL);
	}
	return (res);
}
