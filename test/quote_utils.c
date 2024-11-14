/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:30:15 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/14 11:33:26 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this file is for the interpretation of the quotes



int is_quote(char *string)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (string[i])
	{
		if (string[i] == '"' || string[i] == '\'')
			check += 1;
		i++;
	}
	if (check == 0)
		return (0);
	if ((check % 2) == 0)//error reliee a la simple quote
		return (1);
	else
		return (0);
}

static void state (t_quote *data, int i)
{
    if (i == 0)
    {
        data->lock = 1;
        data->simple += 1;
        if (data->simple % 2 == 0)
            data->lock = 0;   
    }
    if (i == 1)
    {
        data->lock = 2;
        data->duo += 1;
        if (data->duo % 2 == 0)
            data->lock = 0;
    }
}

int quote_number(char *argv)
{
    int i;
    int num;
    t_quote data;

    i = 0;
    num = 0;
    data.duo = 0;
    data.lock = 0;
    data.simple = 0;
    while (argv[i])
    {
        if (argv[i] == '\'' && data.lock != 2)
        {
            state(&data, 0);
            num++;
        }
        if (argv[i] == '"' && data.lock != 1)
        {
            state(&data, 1);
            num++;
        }
        i++;
    }
    return (num/2);
}
/*
char *reform(char *arg)//reformuler les chars avec des quotes
{
    int i;
    int state;
    char *
    
    i = 0;
    state = is_quote(arg);
    if (state == 0)
        return (arg);
    
}
*/