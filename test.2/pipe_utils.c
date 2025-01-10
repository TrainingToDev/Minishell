/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 09:20:01 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-10 09:20:01 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_pipe(char *input)//but : ahafantarana oe misy pile d'execution firy
{
	int i;
	int proc;

	i = 0;
	proc = 1;
	while (input[i])
	{
        i = quote_case(input, i);
		if (input[i] == '|')
			proc++;
		i++;
	}
	return (proc);
}

int valid_pipe(char *input)//laisee passer les espaces apres pipe
{
    int i;
    int index;
    int num;

    i = 0;
    index = 0;
    num = 1;
    while (input[i] != '\0')
    {
        i = quote_case(input, i);
        if (input[i] == '|' && index == 0 && input[i])
        {
            index = 1;
            i++;
            while (input[i] && input[i] != '|')
            {
                i = quote_case(input, i);
                i++;
                index = 0;
            }
            if (input[i] == '|' || input[i] == '\0')
                i--;
            if (index == 0)
                num++; 
        }
        i++;
    }
    return (num);
}
