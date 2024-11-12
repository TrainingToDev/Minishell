/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:12:20 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/12 16:07:56 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_len(char *input, int c, int start)
{
    int i;
    int len;

    i = start;
    len = 0;
    while (input[i])
    {
        if (input[i] == c)
        {
            i++;
            while (input[i] == ' ')
            {
                i++;
                len++;        
            }
            while (input[i] != ' ')
            {
                i++;
                len++;
            }
            return (len);
        }
        i++;
    }
    return (-1);
}

static char **get_file(char **in_file, char *input, int num, int c)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    while (input[i] && (j < num))
    {
        if (input[i] == c)
        {
            i++;
            len = get_len(input, c, i);
            in_file[j] = ft_substr(input, i, len);
            j++;            
        }
        i++;
    }
    return (in_file);
}

char **input_file(char *input)//malloc a free a chaque commande 
{
	char **in_file;
    int num;

    num = get_number_of(input, '>');
    if (num == 0)
    { 
        return (NULL);
    }
	in_file = (char**)malloc(sizeof(char*) * num + 1);
	if (!in_file)
		return (NULL);
    printf ("->%i\n", num);
    in_file = get_file(in_file, input, num, '>');
    return (in_file);
}

char **output_file(char *input)//malloc a free a chaque commande 
{
	char **out_file;
    int num;

    num = get_number_of(input, '<');
    if (num == 0)
    {
        return (NULL);
    }
	out_file = (char**)malloc(sizeof(char*) * num + 1);
	if (!out_file)
		return (NULL);
    out_file = get_file(out_file, input, num, '<');
    return (out_file);
}