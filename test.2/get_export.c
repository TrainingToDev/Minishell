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

static t_export *new_export(char *env)
{
    t_export *exp;
    int i;
    int a;

    exp = (t_export*)malloc(sizeof(t_export));
    if (!exp)
        return (NULL);
    i = 0;
    exp->proto = ft_strdup("declare -x ");
    while (env[i] != '=' && env[i])
        i++;
    exp->var = get_string(env, 0, i, '=');
    i++;
    a = i;
    while (env[i])
        i++;
    exp->value = get_string(env, a, (i - a), '\0');
    exp->next = NULL;
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

    exp =  new_export(env[0]);
    i = 1;
    while (env[i])
    {
        add_new_exp(&exp, new_export(env[i]));
        i++;
    }
    return (exp);
}