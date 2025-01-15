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

static char *copy_after(char *input, int i, int len)
{
    int j;
    int k;
    char *new;

    j = 0;
    k = 0;
    new = (char*)malloc(sizeof(char) * (ft_strlen(input) - len + 1));
    if (!new)
        return (NULL);
    while (input[k])
    {
        if (k == i && len > 0)
        {
            new[j++] = input[k++];
            while (len-- > 0)
                k++;
        }
        else
            new[j++] = input[k++];
    }
    new[j] = '\0';
    free(input);
    return (new);
}
static int get_space_len(char *input, int i)
{
    int len;

    len = 0;
    i++;
    while (input[i] && is_space(input[i]) == 1)
    {
        len++;
        i++;
    }
    return (len);
}
static char *copy_before(char *str, int i)
{
    char *new;
    int j;
    int k;

    k = 0;
    j = 0;
    new = (char*)malloc(sizeof(char) * ft_strlen(str) + 2);
    if (!new)
        return (NULL);
    while (str[k])
    {
        if (i == j)
        {
            new[j] = ' ';
            j++;
        }
        else
            new[j++] = str[k++]; 
    }
    new[j] = '\0';
    free (str);
    return (new);
}


char *change(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '>' || input[i] == '<')
        {
            if (i != 0 && is_space(input[i - 1]) == 0 && input[i -1] != '>' && input[i - 1] != '<')
                input = copy_before(input, i);
        }
        i++;
    }
    i = 0;
    while (input[i])
    {
        if (input[i] == '>' || input[i] == '<')
        {
            if (input[i + 1] && is_space(input[i + 1]) == 1)
                input = copy_after(input, i, get_space_len(input, i));
        }
        i++;
    }
    return (input);    
}
