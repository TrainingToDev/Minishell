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

static int count_exp(char *input)
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
        if (input[i] == '\'' || input[i] == '"')
        {
            i = quote_case(input, i);
            if (input[i + 1])
                i++;
            while (input[i] && input[i] != '$' && input[i] != '\'' && input[i] != '"')
                i++;
            return (i);
        }
        i++;
    }
    return (-1);
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
        printf ("char : %c\n", input[i]);
        lenght = len(input, i) - i  + 1;
        if (i != 0)
            expand[j] = ft_substr(input, i, lenght);
        if (i == 0)
            expand[j] = ft_substr(input, i, lenght);
        printf("splitted : %s -> len : %i\n", expand[j], lenght);
        i += lenght;
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