/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-03 11:05:24 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-03 11:05:24 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_var(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '$')
            count++;
        i++;
    }
    return (count);
}

char *new_var(char *old_var, t_env *env)
{
    int i;

    i = 0;
    while (/* condition */)
    {
        /* code */
    }
    
}


char *input(char **splitted, t_env *env)
{

}
