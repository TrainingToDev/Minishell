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

int count(char *split)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(split[i])
    {
        if(i == 0 && split[i] != '$')
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
        i++;
    }
    printf("nbr len : %i\n", len);
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
    (void)env;
    while (split[i])
    {
        len = get_len(split, i) - i;
        new[j] = ft_substr(split, i, len);
        printf("-------for index %i----------\n", j);
        printf("secund split : %s(fin)\n", new[j]);
        j++;
        i += len;
    }
    new[j] = NULL;
    return (new);
}

char **secund_split(char *split, t_env *env)//mahazo tableau milsy an'ilay expand tsotra
{
    char **new;

    (void)env; 
    new = (char**)malloc(sizeof(char*) * count(split) + 1);
    if (!new)
    {
        printf("null\n");
        return (NULL);
    }
    new = split_secund(new, split, env);
    return (new);
}