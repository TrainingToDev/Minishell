/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:17:19 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/05 12:14:55 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env *last_env(t_env *env)
{
    if (!env)
        return (NULL);
    while (env->next != NULL)
        env = env->next;
    return (env);
}

void	add_new_env(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		last_env(*lst)->next = new;
	else
		(*lst) = new;
}
int list_size(t_env *env)
{
	int i;

	i = 1;
	while (env->next != NULL)
	{
		env = env->next;
		i++;
	}
	return (i);
}