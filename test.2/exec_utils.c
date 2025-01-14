/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-14 10:51:52 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-14 10:51:52 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_arg(t_token *tok)//count the arg we will add to execve function
{
    int i;
    t_token * tmp;

    tmp = tok;
    i = 0;
    while (tmp)
    {
        if (tmp->state != 1)
            i++;
        tmp = tmp->next;
    }
    return (i);
}

char **get_arg(t_token *t, int len)
{
    char **arg;
    int i;
    t_token *tok;

    tok = t;
    arg = (char**)malloc(sizeof(char *) * (len + 1));
    if (!arg)
        return (NULL);
    i = 0;
    while (tok)
    {
        if (tok->state == 6)
        {
            arg[i] = ft_strdup(tok->token);
            printf ("arg : %s\n", arg[i]);
            i++;
        }
        tok = tok->next;
    }
    arg[i] = "\0";
    return (arg);
}

static char *get_path(char *path)//get of the '=' in the value 
{
    char *new_path;
    int i;
    int j;

    i = 1;
    j = 0; 
    new_path = (char *)malloc(sizeof(char) * ft_strlen(path));
    if (!new_path)
        return (NULL);
    while (path[i])
    {
        new_path[j++] = path[i++]; 
    }
    new_path[j] = '\0';
    return(new_path);
}


char **get_all_path(t_env *env)
{
    char *input;
    char **path;
    t_env *temp;
     int i;

     i = 0;
    temp = env;
    while (temp)
    {
        if (ft_strncmp("PATH", temp->var, ft_strlen("PATH")) == 0)
            input = get_path(temp->value);
        temp = temp->next;
    }
    path = ft_split(input, ':');
    free (input);
    return (path);
}

