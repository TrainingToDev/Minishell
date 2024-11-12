/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:58:06 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/12 15:38:45 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_number_of(char *input, int c)//but : ahafantarana misy an'ilay caractere c firy
{
	int i;
	int proc;

	i = 0;
	proc = 0;
	while (input[i])
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
		if (input[i] == c)
			proc++;
		i++;
	}
	return (proc);
}
