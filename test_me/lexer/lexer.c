/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:57 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 11:20:19 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need for refactoring and big test
// space infini not manage


t_token	*lexer(const char *input)
{
	t_token	*tokens;
	size_t	i;

	if (!input)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (is_operator(&input[i]))
			add_operator_token(&tokens, input, &i);
		else if (is_quote(input[i]))
			add_quoted_token(&tokens, input, &i);
		else
			add_word_token(&tokens, input, &i);
	}
	if (!tokens)
	{
		display_error("Lexer error: Failed to add token");
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}

int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

int	validate_pipe_tokens(t_token *current)
{
	if (current->type == TOKEN_PIPE)
	{
		if (!current->next)
		{
			display_syntax_error("newline");
			return (0);
		}
		if (current->next->type == TOKEN_PIPE)
		{
			display_syntax_error("|");
			return (0);
		}
	}
	return (1);
}

int	validate_redirection_tokens(t_token *current)
{
	if (is_redirection_token(current->type))
	{
		if (!current->next)
		{
			display_syntax_error("newline");
			return (0);
		}
		if (current->next->type != TOKEN_WORD)
		{
			display_syntax_error(current->value);
			return (0);
		}
	}
	return (1);
}

int	validate_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (!validate_pipe_tokens(current))
			return (0);
		if (!validate_redirection_tokens(current))
			return (0);
		current = current->next;
	}
	return (1);
}

void	expand_arguments(t_minishell *shell, t_command *cmd)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->argv[i])
	{
		expanded = expand_variables(shell, cmd->argv[i]);
		if (expanded)
		{
			free(cmd->argv[i]);
			cmd->argv[i] = expanded;
		}
		i++;
	}
}
