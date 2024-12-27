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

int	exact_command(char *data, char *command)
{
	int	i;

	i = 0;
	if (ft_strlen(data) != ft_strlen(command))
	{
		// printf("%i->%i\n", (int)ft_strlen(data) , (int)ft_strlen(command));
		return (0);
	}
	while (data[i])
	{
		if (data[i] != command[i])
			return (0);
		i++;
	}
	return (1);
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

