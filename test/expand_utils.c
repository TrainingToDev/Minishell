/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-03 11:49:27 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-03 11:49:27 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_div(char *old_var)
{
    int i;
    int count;

    i = 0;
    count = 1;
    while (old_var[i])
    {
        while (old_var[i] == '$' && old_var[i])
            i++;
        if (old_var[i - 1] == '$' && is_alphanum(old_var[i]) ==  1)
            count++;
        i++;
    }
    return (count);
}

static int count_len(char *str,  int start)
{
    int i;

    i = start;
    while (str[i])
    {
        if (str[i] == '$' && i != start)
            return (i);
        else if (str[i] == '$' && i == start)
        {
            while (is_alphanum(str[i]) == 1 && str[i])
                i++;
            return (i);
        }
        else
            i++;
    }
    return (i);
}

static char **split_secund(char *str, char **split, int count)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i] && j < count)
    {
        
        j++;
    }
    
}

char *secund_split(char *str)
{
    char **split;
    char *result;

    split = (char **)malloc(sizeof(char *) * count_div(str) + 1);
    if (!split)
        return (NULL);
    split = ;//replace
    result = ;//join after replace
    free(split);
    return (result);
}