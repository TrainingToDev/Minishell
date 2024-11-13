/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:12:20 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/13 13:23:02 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int get_len(char *input, int c, int start)//sert a trouver la taille de file[i]
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
            while (input[i] == ' ' && input[i] != '\0')
            {
                i++;
                len++;
                printf("%c->%i\n", input[i], len);
            }
            while (input[i] != ' ' && input[i] != c && input[i] != '\0')
            {
                i++;
                len++;
                printf("%c->%i\n", input[i], len);
            }
            return (len);
        }
        i++;
    }
    return (len);
}
*/

static int get_len(char *input, int c, int start)
{
    int i;
    int check;
    int len;

    i = start;
    check = 0;
    len = 0;
    while (input[i])
    {
        if (input[i] == ' ' && check == 0)
        {
            len++;
        }
        if (input[i] != ' ' && input[i] != c)
        {
            check = 1;
            len++;
        }
        i++;
    }
    return (len);
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
            if (len == 0)
            {
                printf ("i'm here\n");
                return (NULL);
            }
            in_file[j] = ft_substr(input, i, len);
            printf ("%s\n", in_file[j]);
            j++;
        }
        i++;
    }
   // in_file[j] = NULL;
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