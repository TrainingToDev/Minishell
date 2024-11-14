/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:47:13 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/14 16:40:53 by miaandri         ###   ########.fr       */
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

char **get_exec(char *input)
{
    char **data;
    
    if (valid_pipe(input) != check_pipe(input))
    {
        free(input);
        write (2, "NO VALID PIPE\n", 14);
        return (NULL);
    }
    else 
        data = get_pile(input);
    free(input);
    return (data);
}
