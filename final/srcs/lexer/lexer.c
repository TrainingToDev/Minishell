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
	char	*cls;
	char	*cnt;
	int		empty;
	int		open_count;

	empty = 0;
	open_count = 1;
	if (input[0] == '(' && input[1] == '(')
	{
		cls = check_close(input, &open_count);
		if (*cls == ')' && *(cls + 1) == ')' && (*(cls + 2) == '\0' 
		|| ft_isspace(*(cls + 2))) && open_count == 1)
		{
			cnt = input + 2;
			while (cnt < cls)
			{
				if (!ft_isspace(*cnt))
					empty = 1;
				cnt++;
			}
			return (empty || cnt == cls);
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
	if ((input[0] == '\'' && input[1] == '\'' && input[2] == '\0')
		|| (input[0] == '"' && input[1] == '"' && input[2] == '\0'))
	{
		print_error(E_CMD, "'' ", ERR_CMD);
		ft_putstr_fd(": cmd not found\n", STDERR_FILENO);
		return (1);
	}
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
