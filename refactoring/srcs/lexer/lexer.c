/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:57 by herandri          #+#    #+#             */
/*   Updated: 2024/11/29 23:31:45 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	size_t	i;

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
	if (!tokens)
		return (0);
	if (!validate_syntax(tokens))
		return (0);
	return (1);
}

static int	is_double_par(char *input)
{
	char	*closing;
	char	*content;

	if (input[0] == '(' && input[1] == '(')
	{
		closing = input + 2;
		while (*closing && *closing != ')')
			closing++;
		if (*closing == ')' && *(closing + 1) == ')')
		{
			content = input + 2;
			while (content < closing)
			{
				if (!ft_isspace(*content))
					return (1);
				content++;
			}
		}
	}
	return (0);
}

static int	special_cases(char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	if (*input == '\0')
		return (1);
	if ((input[0] == ':' || input[0] == '!')
		&& (input[1] == '\0' || input[1] == ' '))
		return (1);
	if (is_double_par(input))
		return (1);
	return (0);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	if (!input || *input == '\0')
		return (NULL);
	if (special_cases(input))
		return (NULL);
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
