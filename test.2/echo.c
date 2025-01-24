/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:21:52 by miaandri          #+#    #+#             */
/*   Updated: 2024/12/22 21:18:54 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_option(t_token *tok)//state 1 : option exist
{
    t_token *temp;

    temp = tok; 
    while(temp)
    {
        if (ft_strncmp(temp->token, "-n", ft_strlen("-n")) == 0)
            return (1);
        temp = temp->next;
    }
    return (0);
}

int echo_command(t_token **token)
{
    t_token *temp;
    int i;

    temp = (*token);
    i = 0;
    if (checking_redir((temp)) == 1)
        printf("need redirection function\n");//function redirection
    while((temp))
    {
        if ((temp)->state == 6)
        {
            if (ft_strncmp((temp)->token, "-n", ft_strlen("-n")) != 0)
            {
                if (i != 0)
                    printf(" ");
                printf("%s", (temp)->token);
                i++;
            }
        }
        (temp) = (temp)->next;
    }
    if (check_option((*token)) == 0)
        printf("\n");
    return(0);//valeur de retour ny $?
}