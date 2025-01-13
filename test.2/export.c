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

//should handle numeric argument == OK 
//if export u=i + export u -> "u=i" 
// export u -> "u"

static int is_env(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '=')
        {
            if (arg[i + 1])
                return (1);
            return (2);
        }
        i++;
    }
    return (0);
}

static int export(t_export *exp)//export without option and argument
{
    while (exp)
    {
        printf("%s", exp->proto);
        printf("%s", exp->var);
        printf("%s\n", exp->value);
        exp = exp->next;
    }
    return (0);
}

static void remplace(t_export **exp, char *token, int i)//rempace the exp->value 
{
    t_export *temp;

    temp = (*exp);
    while(i > 0)
    {
        i--;
        temp = temp->next;
    }
    free(temp->value);
    temp->value = get_value(token);
}
static void env_remplace(t_env **exp, char *token, int i)//rempace the env->value 
{
    t_env *temp;

    temp = (*exp);
    while(i > 0)
    {
        i--;
        temp = temp->next;
    }
    free(temp->value);
    temp->value = get_value(token);
}

static int command_export(t_env *env, char *token, t_export *exp)
{
    int state_exp;
    int state_env;

    state_exp = existing(get_var(token), exp);
    state_env = exist_env(get_var(token), env);
    token = get_off_quote(token, count_quote(token));
    if (all_num(token) == 0)
    {
        write (2, "export `&token' : non valid identifier\n", (ft_strlen(token) + 33));
        return (1);
    }
    if (state_exp >= 0)
        remplace(&exp, token, state_exp);
    if (state_env >= 0)
        env_remplace(&env, token, state_env);
    if (state_env < 0)
    {
        if(is_env(token) == 1)
            add_new_env(&env, new_env(token));
        if(is_env(token) == 2)
            add_new_env(&env, new_env(reform(token)));
    }
    if (state_exp < 0)
        add_new_exp(&exp, new_export(reform(token)));
    return (0);
}

int export_command(t_env *env, t_token **token, t_export *exp)
{
    t_export *temp2;
    int state;

    temp2 = exp;
    state = 0;
    if (checking_redir((*token)) == 1)
        printf("need redirection function\n");
    if ((*token)->next == NULL)
        return (export(temp2));
    while ((*token))
    {
        if ((*token)->state == 6 && is_option((*token)->token) == 1)
        {
            write (2,"No argument is tolerated\n", 25); // update
            return (2);////$? = 2 when the option don ' t exist
        }
        else if ((*token)->state == 6)
        {
            if (command_export(env, (*token)->token, exp) == 1)
                state = 1;
        }
        (*token) = (*token)->next;
    }
    if (state == 1)
        return (1);//value of $? in case one of the error command
    return (0);
}
