/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:21:41 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 14:10:34 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_string(char *env, int i, int len, int c)
{
    char *value;
    int a;

    value = (char*)malloc(sizeof(char) * len + 1);
    if (!value)
        return (NULL);
    a = 0;
    while (env[i] != c && env[i] != '\0')
    {
        value[a] = env[i];
        a++;
        i++;
    }
    value[a] = '\0';
    return (value);
}

static t_env *new_env(char *env)//ampiasana @ export
{
    t_env *data;
    int i;
    int a;

    data = (t_env*)malloc(sizeof(t_env));
    if (!data)
        return (NULL);
    i = 0;
    while (env[i] != '=')
        i++;
    data->var = get_string(env, 0, i, '=');
    i++;
    a = i;
    while (env[i])
        i++;
    data->value = get_string(env, a, (i - a), '\0');
    data->next = NULL;
    if (env)
        free(env);
    return (data);
}

static void add_new_env(t_env **lst, t_env *new)
{
    if (!lst || !new)
        return ;
    while ((*lst)->next != NULL)
        *lst = (*lst)->next;
    (*lst) = new;
}

t_env *get_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        
    }
}
