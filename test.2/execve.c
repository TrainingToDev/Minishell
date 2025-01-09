/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-27 11:15:53 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-27 11:15:53 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_path(char *path)
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
    printf("new path : %s\n", new_path);
    return(new_path);
}


char **get_all_path(t_env *env)
{
    char *input;
    char **path;
    t_env *temp;
    // int i;

    // i = 0;
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
/*
void new_proc(t_token **tok, t_env *env)
{
    pid_t pid;

    pid = fork();
    if (pid > 0)
    {

    }
    if (pid == 0)
    {
        //waitpid(pid , );
    }
}
*/