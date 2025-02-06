/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:44:24 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/01 23:43:47 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(t_env_var *env)
{
	t_env_var	*cur;
	int			count;

	count = 0;
	cur = env;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

char	**convert_env_list(t_env_var *env_list)
{
	t_env_var	*cur;
	char		**env_array;
	char		*entry;
	int			i;

	env_array = malloc(sizeof(char *) * (count(env_list) + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	cur = env_list;
	while (cur)
	{
		entry = join_free(ft_strjoin(cur->key, "="), cur->value, 1);
		if (!entry)
		{
			free_str_array(env_array);
			return (NULL);
		}
		env_array[i++] = entry;
		cur = cur->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
