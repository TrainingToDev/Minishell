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

static int change(char *splitted)
{
    int i;

    i = 0;
    while(splitted[i])
    {
        i = case_quote(input, i);
        if (splitted[i] == '$')
            return(1);
        i++;
    }
    return (0);
} 


char *expand(char **splitted, char input)
{
    char *exp;
    int i;

    i = 0;
    while(splitted[i])
    {
        //function maka ilay $de manova azy
        i++;
    }
    exp = ;//join splitted
    free(input);
}
