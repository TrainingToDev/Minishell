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

static int count_exp(char *input)//count chaine separer par les $ et "" et ''
{
    int i;
    int count;

    i = 0;
    count = 1;
    while (input[i])
    {
        if (quote_case(input, i) != i)
            count++;
        i = quote_case(input, i);
        if (input[i] == '$')
            count++;
        i++;
    }
    //printf ("count : %i\n", count);
    return(count);
}

static int len(char *input, int start)
{
    int i;

    i = start;
    printf("start : %i\n", i);
    while (input[i])
    {
        if (input[i] == '$')
            return (i);
        else if (input[i] == '\'' )
        {
            i = quote_case(input, i);
            return (i + 1);
        }
        else if (input[i] == '"')
        {
            i = quote_case(input, i);
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
    while (j < count_exp(input) && input[i])
    {
        lenght = len(input, i) - i;
        printf("len : %i\n", lenght);
        if (i == 0)
            expand[j] = ft_substr(input, i, lenght);
        else
            expand[j] = ft_substr(input, i - 1, lenght + 1);
        printf("->: %s\n", expand[j]);
        i += lenght + 1;
        j++;
    }
    expand[j] = "\0";
    return (expand);
}


char **split_expand(char *input)
{
    char **expand;

    expand = (char**)malloc(sizeof(char*) * count_exp(input) + 1);
    if (!expand)
        return (NULL);
    expand = split_exp(expand, input);
    return (expand);
}