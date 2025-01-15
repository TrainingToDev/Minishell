/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:21:41 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/09 12:34:04 by herandri         ###   ########.fr       */
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
	while (env[i] != c && env[i] != '\0' && a < len) // check overflow env
	{
		value[a] = env[i];
		//printf("test : %c ->%c\n", value[a] , env[i]);
		a++;
		i++;
	}
	value[a] = '\0';
	//free(env);
	return (value);
}

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

t_env	*new_env(char *env, int state) ///malloc ato seulement ctl+D vao mifree
{
	t_env *data;
	int i;
	int a;

	data = (t_env *)malloc(sizeof(t_env));
	if (!data)
		return (NULL);
	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	data->var = get_string(env, 0, i, '=');
	i++;
	a = i;
	while (env[i])
		i++;
	data->value = get_string(env, a, (i - a), '\0');
	data->next = NULL;
	if (state == 1)
		free(env);
	return (data);
}

t_env	*get_env(char **env)
{
	int	i;
	t_env *list;

	list = new_env(env[0], 0);
	i = 1;
	while (env[i])
	{
		add_new_env(&list, new_env(env[i], 0));
		i++;
	}
	return (list);
}
