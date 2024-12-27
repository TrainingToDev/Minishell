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
/*
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
*/
/*
int export_command(t_env *env, t_parse *data)
{
    if (exact_command(data->command, "export") != 1)
        return (0);
   // if (data->option != NULL)
        return (0);
    if (is_variable(data->param) != 1)
        return (0);
    add_new_env(&env, int add_new_var(t_parse *data, t_env *var);new_enve(data->param));
    free_struct(data);
    return (1);
}
*/

//one thing confusing no option no argument so with option should be an error ?

int env_command(t_env *env, t_token **token)
{
    t_env   *temp;

    temp = env;
    if (checking_redir((*token)) == 1)
        printf ("need redirection function\n");//function redirection 
    while ((*token))
    {
        if ((*token)->state == 6)
        {
            write (2,"No argument is tolerated\n", 27);
            //function de free ending command program
            return (-1);//valeur de retour $? (mbola tsy hay)
        }
        (*token) = (*token)->next;
    }
    while (temp)
    {
        printf("%s", temp->var);
        printf("%s\n", temp->value);
        temp = temp->next;
    }
    return (0);//valeur de retour $?
}
