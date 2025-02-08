/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:48:29 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 01:08:43 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*map_token(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("TOKEN_WORD");
	else if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	else if (type == TOKEN_APPEND)
		return ("TOKEN_APPEND");
	else if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	else if (type == TOKEN_AND)
		return ("TOKEN_AND");
	else if (type == TOKEN_OR)
		return ("TOKEN_OR");
	else if (type == TOKEN_LPAREN)
		return ("TOKEN_LPAREN");
	else if (type == TOKEN_RPAREN)
		return ("TOKEN_RPAREN");
	else
		return (NULL);
}

static char	*get_token_type_name(t_token_type type)
{
	char	*type_name;

	type_name = map_token(type);
	if (type_name != NULL)
		return (type_name);
	else if (type == TOKEN_UNKNOWN)
		return ("TOKEN_UNKNOWN");
	else
		return ("UNKNOWN_TYPE");
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token Type: %s, Value: [", get_token_type_name(current->type));
		if (current->value)
			printf("%s", current->value);
		else
			printf("NULL");
		printf("], Expand: %d\n", current->expand);
		current = current->next;
	}
}
