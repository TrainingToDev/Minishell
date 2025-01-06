/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_off_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-08 08:42:24 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-08 08:42:24 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_quote(char *command)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (command[i] == '\'')
		{
			i++;
			while (command[i] && command[i] != '\'')
				i++;
			if (command[i] == '\'')
				i++;
			count++;
		}
		else if (command[i] == '"')
		{
			i++;
			while (command[i] && command[i] != '"')
				i++;
			if (command[i] == '"')
				i++;
			count++;
		}
		else
			i++;
	}
	return(count);
}

static char *copy(char *new, char *old)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] == '\'')
		{
			i++;
			while (old[i] && old[i] != '\'')
				new[j++] = old[i++];
			i++;
		}
		else if (old[i] == '"')
		{
			i++;
			while (old[i] && old[i] != '"')
				new[j++] = old[i++];
			i++;
		}
		else
			new[j++] = old[i++];
	}
	new[j] = '\0';
	return (new);
}


char *get_off_quote(char *old, int count)//count==count_quote;
{
	char *new;

	new = (char*)malloc(sizeof(char) * (ft_strlen(old) - (count * 2) + 1));
	if (!new)
		return (NULL);
	new = copy(new, old);
	free(old);
	return (new);
}