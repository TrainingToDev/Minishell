/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-26 10:18:26 by miaandri          #+#    #+#             */
/*   Updated: 2024-11-26 10:18:26 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int case_quote(char *input, int i)
{
    if (input[i] == '\'')
    {
        i++;
        while(input[i] && input[i] != '\'')
            i++;
    }
    return (i);
}

static int count_exp(char *input)//count chaine separer par les $ et "" et ''
{
    int i;
    int count;

    i = 0;
    count = 1;
    while (input[i])
    {
        if (case_quote(input, i) != i)
            count++;
        i = case_quote(input, i);
        if (input[i] == '$')
            count++;
        i++;
    }
    printf ("expand array : %i\n", count);
    //printf ("count : %i\n", count);
    return(count);
}

static int len(char *input, int start)
{
    int i;

    i = start;
    while (input[i])
    {
        if (input[i] == '$')
            return (i);
        else if (input[i] == '\'' )
        {
            i = case_quote(input, i);
            return (i + 1);
        }
        else
            i++;
    }
    return (i);
}
static char **split_exp(char **expand, char *input)
{
    int i;
    int j;
    int lenght;

    i = 0;
    j = 0;
    while (input[i])
    {
        lenght = len(input, i) - i;
        printf("len : %i\n", lenght);
        if (i == 0)
            expand[j] = ft_substr(input, i, lenght);
        else
            expand[j] = ft_substr(input, i - 1, lenght + 1);
        printf("splitted: %s(fin)\n", expand[j]);
        i += lenght + 1;
        j++;
    }
    printf ("nulled : %i\n", j);
    expand[j] = NULL;
    return (expand);
}


/*
int count_exp(char *input)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (input[i])
    {
        if (input[i] == '"')
        {
            i = quote_case(input, i);
            count++;
        }
    }
    
}

*/
char **split_expand(char *input)
{
    char **expand;

    expand = (char**)malloc(sizeof(char*) * count_exp(input) + 1);
    if (!expand)
        return (NULL);
    expand = split_exp(expand, input);
    return (expand);
}


