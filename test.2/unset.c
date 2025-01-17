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

void list_get_off(t_env *env, char *find)
{
    t_env *temp;
    t_env *lst;

    temp = env;
    while (temp)
    {
        if (ft_strncmp(find, temp->var, ft_strlen(find)) == 0)
        {
            lst = temp->next;
        }
        temp = temp->next;
    }
}

int unset_command(t_env *env, t_token **token)
{
    t_env *temp;
    t_token *tok;

    temp = env;
    tok = (*token);
    if (checking_redir((*token)) == 1)
        printf("need redirection function\n");
    while (tok)
    {
        if (tok->state == 6 && is_option(tok->token) == 1)
        {
            write (2,"No option is tolerated\n", 23); // update
            return (2);////$? = 2 when the option don ' t exist   
        }
        else if (tok->state == 6)
        {

        }
        tok = tok->next;
    }
    return (0);
}
