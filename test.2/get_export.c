/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-06 07:19:03 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-06 07:19:03 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export *new_export(char *env, int state)
{
    t_export *exp;

    exp = NULL;
    exp = (t_export*)malloc(sizeof(t_export));
    if (!exp)
        return (NULL);
    exp->proto = ft_strdup("declare -x ");
    exp->var = get_var(env);
    exp->value = get_value(env);
    exp->next = NULL;
    if (state == 1)
        free(env);
    return (exp);
}
static t_export *last_exp(t_export *exp)
{
    if (!exp)
        return (NULL);
    while (exp->next != NULL)
        exp = exp->next;
    return (exp);
}

void add_new_exp(t_export **lst, t_export *new)
{
    if (!lst || !new)
        return ;
    if (*lst)
        last_exp(*lst)->next = new;
    else
        (*lst) = new;
}

t_export *get_export_list(char **env)
{
    int i;
    t_export *exp;

    exp =  new_export(env[0], 0);
    i = 1;
    while (env[i])
    {
        add_new_exp(&exp, new_export(env[i], 0));
        i++;
    }
    return (exp);
}