/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:58:06 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/15 10:31:05 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int quote_case(char *input, int i)
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
	return (i);
}

int get_number_of(char *input, int c)//but : ahafantarana misy an'ilay caractere c firy
{
	int i;
	int proc;

	i = 0;
	proc = 0;
	while (input[i])
	{
		i = quote_case(input, i);
		if (input[i] == c)
			proc++;
		i++;
	}
	return (proc);
}

int valid_redir(char *input)//count the valid redirection 
{
	int i;

	i = 0;
	while (input[i])
	{
		i = quote_case(input, i);
		if (input[i] == '>' && input[i + 1] )
		i++;
	}
	
}
