/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 07:21:12 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-13 07:21:12 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int existing(char *var, t_export *exp)
{
    t_export *temp;
    int i;

    i = 0;
    temp = exp;
    if (!var)
        return (-1);
    while(temp)
    {
        if (ft_strncmp(var, temp->var, ft_strlen(var)) == 0)
        {
            free(var);
            return (i);
        }
        i++;
        temp = temp->next;
    }
    free (var);
    return (-1);//don't exist state
}

int exist_env(char *var, t_env *exp)
{
    t_env *temp;
    int i;

    i = 0;
    temp = exp;
    while(temp)
    {
        if (ft_strncmp(var, temp->var, ft_strlen(var)) == 0)
        {
            free(var);
            return (i);
        }
        i++;
        temp = temp->next;
    }
    free (var);
    return (-1);//don't exist state
}