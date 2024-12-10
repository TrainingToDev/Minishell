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

int change2(char *splitted)
{
    int i;

    i = 0;
    while(splitted[i])
    {
        i = case_quote(splitted, i);
        if (splitted[i] == '$')
        {
            //printf("with\n");
            return(1);
        }
        i++;
    }
    return (0);
} 

char *expand(char **splitted)
{
    //char *exp;
    int i;

    i = 0;
    while(splitted[i])
    {
        //function maka ilay $de manova azy
        if (change2(splitted[i]) == 1)
        {
            printf ("%s\n", splitted[i]);
            printf ("-----here secund split-----");
            secund_split(splitted[i], NULL);
        }
        i++;
    }
    //exp = ;//join splitted
    //free(input);
    return (NULL);
}
