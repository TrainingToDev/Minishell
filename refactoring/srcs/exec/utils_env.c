/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:44:24 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 09:52:26 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count(t_env_var *env)
{
	t_env_var	*current;
    int count;

    count = 0;
    current = env;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

char	**convert_env_list(t_env_var *env_list)
{
	t_env_var	*current;
	char		**env_array;
	char		*entry;
	int			i;

	env_array = malloc(sizeof(char *) * (count(env_list) + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	current = env_list;
	while (current)
	{
		entry = ft_strjoin_free(ft_strjoin(current->key, "="), current->value, 1);
		if (!entry)
		{
			free_str_array(env_array);
			return (NULL);
		}
		env_array[i++] = entry;
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
