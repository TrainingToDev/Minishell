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

static int count(char *split)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(split[i])
    {
        if (split[i] != '$' && i = 0)
        {
            while(split[i] && split[i] != '$')
                i++;
            len++;
        }
        else if (split[i] == '$')
        {
            i++;
            while(split[i] && is_alphanum(split[i]) != 0)
                i++;
            len++;
        }
        else if (split[i] != '$')
        {
            while(split[i] && split[i] != '$')
                i++;
            len++;
        }
    }
    printf("len : %i\n", len);
    return(len);
}
static int get_len(char *split, int start)
{
    int i;

    i = start;
    while(split[i])
    {
        if (i == start && split[i] == '$')
        {
            i++;
            while(split[i] && is_alphanum(split[i]) != 0)
                i++;
            return (i);
        }
        else
        {
            while(split[i] && split[i] != '$')
                i++;
            if (split[i] == '$')
                return (i - 1);
            else
                return (i);
        }
    }
    return (0);
}
static char **split_secund(char **new, char *split, t_env *env)//eto no manova zay ovaina rehetra
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    while (split[i])
    {
        len = get_len(split, i) - i;
        new[j] = ft_substr(input, i, len);
        printf("secund split : %s\n", new[j]);
        j++;
        i += len;
    }
    new[j] = NULL;
    return (new);
}

char **secund_split(char *split)//de avy eo eto atao join voalohany 
{
    char **new;

    new = (char**)malloc(sizeof(char*) * count(split) + 1);
    if (!new)
        return (NULL);
    new = split_secund(new, input)
}