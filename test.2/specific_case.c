/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specific_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-06 07:38:49 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-06 07:38:49 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int name(int c)//this function decide quel caractere supporte les redirections return 0:refa tsy supporteny 
{
    if (c == '>' || c == '<')
        return (2);
    if (c <= 'z' && c >= 'a')
        return (1);
    if (c <= 'Z' && c >= 'A')
        return (1);
    if (c <= '9' && c >= '0')
        return (1);
    if (c == '"')
        return (1);
    return (0);
}

static int check_specific_case(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '>' || input[i] == '<')
        {
            if (input[i - 1] != ' ' && input[i - 1] != '\t' && input[i - 1] != '>' && input[i - 1] != '<' && i != 0)
                return (1);
            if (name(input[i + 1]) == 0)
                return (1);
        }
        i++;
    }
    return (0);
}

static int get_new_len(char *input)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (input[i])
    {
        if (input[i] == '>' || input[i] == '<')
        {
            i++;
            len++;
            if (input[i - 1] != ' ' && input[i - 1] != '\t' && input[i - 1] != '>' && input[i - 1] != '<' && i != 0)
                len++;
            while(name(input[i]) == 0)
                i++;
        }
        else
        {
            len++;
            i++;
        }
    }
    //printf ("len : %i\n", len);
    return (len);
}
static char *copy(char *input, char *reform)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (input[i] && j < get_new_len(input))
    {
        if (input[i] == '>' || input[i] == '<')
        {
            if (input[i - 1] != ' ' && input[i - 1] != '\t' && input[i - 1] != '>' && input[i - 1] != '<' && i != 0)
            {
                reform[j] = ' ';
                j++;
            }
            reform[j++] = input[i++];
            while (name(input[i]) == 0)
                i++;
        }
        else
            reform[j++] = input[i++];
    }
    printf ("g : %i\n", g_sign);
    reform[j] = '\0';
    return (reform);
}

char *change(char *input)
{
    char    *reform;

    if (check_specific_case(input) == 0)
    {
        printf("str : %s\n", input);
        return (input);
    }
    else
    {
        reform = (char*)malloc(sizeof(char) * get_new_len(input)+ 1);
        if (!reform)
            return (NULL);
        reform = copy(input, reform);
        free(input);
        printf("str : %s\n", reform);
        return (reform);
    }
    return (NULL);
}
