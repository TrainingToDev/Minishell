/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-04 08:15:29 by miaandri          #+#    #+#             */
/*   Updated: 2024-11-04 08:15:29 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_variable(char *string)
{
    int i;

    i = 0;
    while (string[i])
    {
        if (string[i] == '=' && i != 0)
        {
            if (string[i] == '=' && string[i + 1] == ' ')
                return (0);
            if (string[i] == '=' && string[i - 1] == ' ')
                return (0);
            return (1);
        }
        i++;
    }
    return (0);
}
static t_env	*new_enve(char *env)
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
	data->value = get_string(env, a, (i - a), ' ');
	data->next = NULL;
    free(env);
	return (data);
}

int export_command(t_env *env, t_parse *data)
{
    if (exact_command(data->command, "export") != 1)
        return (0);
   // if (data->option != NULL)
        return (0);
    if (is_variable(data->param) != 1)
        return (0);
    add_new_env(&env, new_enve(data->param));
    free_struct(data);
    return (1);
}

int env_command(t_env *env, t_parse *data)
{
    if (exact_command(data->command, "env") != 1)
        return (0);
   // if (data->option != NULL)
        return (0);
    if (data->param != NULL)
        return (0);
    while (env)
	{
		printf("%s", env->var);
		printf("%s\n", env->value);
		env = env->next;
	}
    free_struct(data);
    return (1);
}