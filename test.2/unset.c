/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-08 08:48:05 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-08 08:48:05 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_option(char *arg)
{
    int i;
    
    i = 0;
    while (arg[i])
    {
        if (arg[i] == '-' && i == 0)
        {
            i++;
            if (is_alpha(arg[i]) == 1)
                return (1);
        }
        i++;
    }
    return (0);
}
/*
void list_get_off(t_env **env, char *find)
{
    t_env *temp;
    t_env *lst;

    temp = (*env);



}

int unset_command(t_env *env, t_token **token)
{
    t_env *temp;

    temp = env;
    if (checking_redir((*token)) == 1)
        printf("need redirection function\n");
    while ((*token))
    {

        (*token) = (*token)->next;
    }
}
*/