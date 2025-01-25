/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:16:02 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/05 12:06:14 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int chech_variable(t_parse *data)
{
    if (is_variable(data->command) != 1)
        return (0);
    if (data->option != NULL)
        return (0);
    if (data->param != NULL)
        return (0);
    return (1);
}
int add_new_var(t_parse *data, t_env *var)
{
    if (chech_variable(data) != 1)
        return (0);
    add_new_env(&var, new_env(data->command));
    free_struct(data);
    return (1);
}


t_env *local_variable(void)//free @ ctl+D
{
    t_env *var;

    var = (t_env*)malloc(sizeof(t_env));
    if (!var)
        return (NULL);
    var->var = get_string("?=0", 0, 1, '=');
    var->value = get_string("?=0", 2, 2, '\0');
    var->next = NULL;
    return (var);
}