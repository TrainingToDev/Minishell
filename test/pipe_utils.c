/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:47:13 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/18 13:10:21 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int void_pipe(char  *input, int i)
{
    int cpy;

    cpy = i;
    while (i > 0)
    {
        i--;
        if (is_alpha(input[i]) == 1)
            return (1);
    }
    i = cpy + 1; 
    while (input[i] != '|' && input[i])
    {
        if (is_alpha(input[i]) == 1)
            return (1);
        i++;
    }
    write (2, "syntax error near unexpected token `|'\n",40);
    return (-1);
}
int pipe_void(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        i = quote_case(input, i);
        if (input[i] == '|')
        {
            if (void_pipe(input, i) == -1)
                return (-1);
        }
        i++;
    }
    return (0);
}

int check_redir(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '"' || input[i] == '\'')
            i = quote_case(input, i);
        else if (input[i] == '>' || input[i] == '>')
        {
            if (test4(input, i) == -1 || test1(input, i) == -1 ||
                test3(input, i) == -1 || test2(input, i)  == -1)
                    return (-1);
        }
        i++;
    }
    return (0);
}



