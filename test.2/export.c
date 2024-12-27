/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-27 09:58:22 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-27 09:58:22 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//A faire a la maison

static int checking_arg(t_token *tok)
{
    t_token *temp;
    int count;

    temp = tok;
    count = 0;
    while (temp)
    {
        if (temp->state == 6)
            count++;
        temp = temp->next;
    }
    return (count);//nbr of argument
}


int export_commnand(t_env *env, t_token **tok)
{
    if (checking_redir((*tok)) == 1)
        printf ("need function redir\n");//function of redirection
    if (checking_arg(*tok) == 0)
    {
        //affiche fotsiny
    }
    else
    {
        //ajoute A t_export
        //ajoute A t_env
    }
    
    return (0);//valeurs de retour de $?
}