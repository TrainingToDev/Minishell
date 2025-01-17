/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-27 05:21:17 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-27 05:21:17 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void take_all_quote(t_token **tok)
{
    t_token *temp;

    temp = (*tok);
    while (temp)
    {
        if (temp->state == 6)
            temp->token = get_off_quote(temp->token, count_quote(temp->token)); 
        temp = temp->next;
    }
}

int checking_redir(t_token *temp)//redir cheching
{
    t_token *tok;

    tok = temp;
    while (tok)
    {
        if (tok->state == 2)
            return (1);
        else if (tok->state == 3)
            return (1);
        else if (tok->state == 4)
            return (1);
        else if (tok->state == 5)
            return (1);
        tok = tok->next;
    }
    return (0);//without redirection
}