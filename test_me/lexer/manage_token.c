/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:48:29 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 10:12:58 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Method for tokenization, need big test
t_token_type	get_operator_token_type(const char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0) //for bonus
		return (TOKEN_AND);
	else if (ft_strncmp(str, "||", 2) == 0) //for bonus
		return (TOKEN_OR);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (*str == '>')
		return (TOKEN_REDIRECT_OUT);
	else if (*str == '<')
		return (TOKEN_REDIRECT_IN);
	else if (*str == '|')
		return (TOKEN_PIPE);
	else if (*str == '(') // for bonus
		return (TOKEN_LPAREN);
	else if (*str == ')') // for bonus
		return (TOKEN_RPAREN);
	else
		return (TOKEN_UNKNOWN); // Cas d'erreur
}

t_token_type unsupported_redir(const char *input)
{
    if (ft_strncmp(input, "2>", 2) == 0)
        return TOKEN_UNKNOWN;
    if (ft_strncmp(input, "2>>", 3) == 0)
        return TOKEN_UNKNOWN;
    if (ft_strncmp(input, "&>", 2) == 0)
        return TOKEN_UNKNOWN;
    if (ft_strncmp(input, "&>>", 3) == 0)
        return TOKEN_UNKNOWN;
    if (ft_strncmp(input, "<<<", 3) == 0)
        return TOKEN_UNKNOWN;
    if (isdigit(input[0]) && input[1] == '>')
        return TOKEN_UNKNOWN;
    if (isdigit(input[0]) && input[1] == '>' 
        && input[2] == '&' && input[3] == '-')
        return TOKEN_UNKNOWN;
    return TOKEN_WORD;
}

char	*extract_quoted_value(const char *input, size_t *i, int *expand)
{
	char	quote_char;
	size_t	start;
	char	*value;

	quote_char = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (input[*i] != quote_char)
	{
		display_error("Syntax error: Unclosed quote");
		return (NULL);
	}
	*expand = 0;
	if (quote_char == '\"')
		*expand = 1;
	value = ft_substr(input, start, *i - start);
	if (!value)
	{
		display_error("Memory allocation error in extract_quoted_value");
		return (NULL);
	}
	return (value);
}

char	*extract_word_value(const char *input, size_t *i)
{
	size_t	start;
	char	*value;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& !is_operator(&input[*i]) && input[*i] != '\''
		&& input[*i] != '\"')
		(*i)++;
	value = ft_substr(input, start, *i - start);
	if (!value)
	{
		display_error("Memory allocation error in extract_word_value");
		return (NULL);
	}
	return (value);
}
