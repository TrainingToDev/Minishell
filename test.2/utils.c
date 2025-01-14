/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:24:45 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/14 10:47:41 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_space (int c)
{
	if (c == ' ')
		return (1);
	else if (c == '\t')
		return (1);
	return (0);
}

int quote_case(char *input, int i)
{
    if (input[i] == '\'')
	{
		i++;
		while ((input[i] != '\'' && input[i] != '\0'))
			i++;
	}
	if (input[i] == '"')
	{
		i++;
		while ((input[i] != '"' && input[i] != '\0'))
			i++;
	}
    if (input[i] == '\0')
        return (i - 1);
    return (i);
}
int is_alphanum(int c)
{
	if (c <= 57 && c >= 48)
		return (1);
	else if (c <= 122 && c >= 97)
		return (1);
	else if (c <= 90 && c >= 65)
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int is_var(char *token, int start , int len)
{
	int i;

	i = start;
	while (token[i] && i < len)
	{
		if (token[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int is_alphasymb(int c)
{
	if (c <= '9' && c >= '0')
		return (0);
	return (1);
}

int	is_alpha(int c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97))
		return (1);
	return (0);
}

