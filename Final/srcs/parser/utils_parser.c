/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:21:30 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 00:42:26 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parser_advance(t_parser *parser)
{
	t_token	*current;

	current = parser->current;
	if (parser->current)
		parser->current = parser->current->next;
	return (current);
}

int	is_token(t_parser *parser, t_token_type type)
{
	return (parser->current && parser->current->type == type);
}

size_t	process_quotes(const char *value, char *result, size_t i, size_t *j)
{
	char	quote;

	quote = value[i];
	i++;
	while (value[i] && value[i] != quote)
		result[(*j)++] = value[i++];
	if (value[i] == quote)
		i++;
	return (i);
}

char	*clean_quotes(const char *value)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!value)
		return (NULL);
	len = ft_strlen(value);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
			i = process_quotes(value, result, i, &j);
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
	return (result);
}

void	print_indentation(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}
