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
/*
static char *find_redir(t_token *token)
{
    char *redir;
    t_token *temp;

    redir = NULL;
    temp = token;
    while(temp)
    {
        if (temp->state == -5)
            redir = temp->token;
        temp = temp->next;
    }
    return(redir);
}
*/

int echo_command(t_token **token)
{
    t_token *temp;

    temp = (*token);
    if (checking_redir((temp)) == 1)
        printf("need redirection function\n");//function redirection
    while((temp))
    {
        if ((temp)->state == 6)
        {
            if (ft_strncmp((temp)->token, "-n", ft_strlen("-n")) != 0)
                printf("%s ", (temp)->token);//ilay space @farany mbola mila reglena
        }
        (temp) = (temp)->next;
    }
    if (check_option((*token)) == 0)
        printf("\n");
    return(0);//valeur de retour ny $?
}