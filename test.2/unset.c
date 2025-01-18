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
static void del_one(t_env *env, t_export *exp,int state)
{
    if (state == 0)
    {
        free(env->value);
        free(env->var);
        free(env);
        return ;
    }
    if (state == 1)
    {
        free(exp->proto);
        free(exp->value);
        free(exp->var);
        free(exp);
    }
}

void exp_get_off(t_export **env, char *find)
{
    t_export *temp;
    t_export *lst;

    temp = *env;
    if (ft_strncmp(temp->var, find, ft_strlen(find)) == 0)
    {
        (*env) = (*env)->next;
        del_one(NULL, temp, 1);
        return ; 
    }
    temp = *env;
    while (temp && temp->next)
    {
        if (ft_strncmp(find, temp->next->var, ft_strlen(find)) == 0)
        {
            lst = temp->next;
            temp->next = temp->next->next;
            del_one(NULL, lst, 1);
            return ;
        }
        temp = temp->next;
    }
}

void env_get_off(t_env **env, char *find)
{
    t_env *temp;
    t_env *lst;

    temp = *env;
    if (ft_strncmp(temp->var, find, ft_strlen(find)) == 0)
    {
        (*env) = (*env)->next;
        del_one(temp, NULL, 0);
        return ; 
    }
    temp = *env;
    while (temp && temp->next)
    {
        if (ft_strncmp(find, temp->next->var, ft_strlen(find)) == 0)
        {
            lst = temp->next;
            temp->next = temp->next->next;
            del_one(lst, NULL,0);
            return ;
        }
        temp = temp->next;
    }
}

int unset_command(t_env *env, t_export *exp,t_token **token)
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
            env_get_off(&env, tok->token);
            exp_get_off(&exp, tok->token);
        }
        tok = tok->next;
    }
    return (0);
}
