/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:21:41 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/05 12:19:35 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_string(char *env, int i, int len, int c)
{
	char	*value;
	int		a;

	if (c == '\0')
		len = len + 1;
	value = (char *)malloc(sizeof(char) * len + 1);
	if (!value)
		return (NULL);
	a = 0;
	if (c == '\0' || c == ' ')
	{
		value[a] = '=';
		a++; 
	}
	while (env[i] != c && env[i] != '\0')
	{
		value[a] = env[i];
		a++;
		i++;
	}
	value[a] = '\0';
	return (value);
}

t_env	*new_env(char *env) ///malloc ato seulement ctl+D vao mifree
{
	t_env *data;
	int i;
	int a;

	data = (t_env *)malloc(sizeof(t_env));
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
	return (data);
}

t_env	*get_env(char **env)
{
	int	i;
	t_env *list;

	list = new_env(env[0]);
	i = 1;
	while (env[i])
	{
		add_new_env(&list, new_env(env[i]));
		i++;
	}
	return (list);
}
