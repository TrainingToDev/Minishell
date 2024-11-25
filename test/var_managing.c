/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_managing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-25 08:04:16 by miaandri          #+#    #+#             */
/*   Updated: 2024-11-25 08:04:16 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
$$
$$$
$a-z|A-Z|0-9|_
""
export


arc argv , env
env :
t_env : env
*/
//avant get_state


static int count(char *token)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (token[i])
    {
        if (token[i] == '\'' || token[i] == '"')
        {
            i = quote_case(token, i);
            count++;
        }
        i++;
    }
    return (count);
}

static int len(char *token, int start, int c)
{
    int i;

    i = start;
    while (token[i] && token[i] != c)
        i++;
    if (token[i] == c)
        return (i - start);
    return (-1);
}

static t_expand *is_expanded(char *token, int count)
{
    int i;
    int j;
    t_expand *var;

    var = (t_expand*)malloc(sizeof(t_expand) * count);
    if (!var)
        return (NULL);
    i = 0;
    j = 0;
    while (token[i] && j < count)
    {
        if (token[i] == '\'' || token[i] == '"')
        {
            var[j].len = len(token, i + 1, token[i]);
            var[j].start = i;
            j++;
            i += var[j].len; 
        }
        i++;
    }
    return (var);
}
//substr + join no mety indrindra
int check_expand(char *token, t_expand *var, int count)
{
    int j;

    j = 0;
    while (j < count)
    {
        j++;
    }
    
}