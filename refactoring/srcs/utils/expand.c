/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:09:21 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/06 14:09:26 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *compare(char *var, t_env *env)//var == token->value; 
{
    t_env *temp;

    temp = env;
    while (temp)
    {
        if (ft_strncmp(var, temp->var, ft_strlen(var)) == 0)
        {
            free(var);
            var = ft_strdup(temp->value);
            var = ft_substr_free(var, 1, ft_strlen(var) - 1);
            return (var);
        }
        temp = temp->next;
    }
    free (var);
    return ("");
}
