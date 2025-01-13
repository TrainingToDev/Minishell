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

char *real_dir(char **path, char *cmd)
{
    int i;
    char *dir;
    struct stat buf;

    i = 0;
    dir = NULL;
    while (path[i])
    {
        dir = ft_strjoin(path[i], cmd);//cmd = /command
        if (stat(dir, &buf) == 0)
        {
            if (S_ISREG(buf.st_mode) == 1)
            {
                printf ("the path : %s\n", dir);
                return (dir);
            }
        }
        free(dir);
        i++;
    }
    printf ("path not found\n");
    return (NULL);
}

static int len_arg(t_token *tok)//count the arg we will add to execve function
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

void new_proc(t_token **tok, t_env *env)
{
    pid_t pid;
    char *path;

    pid = fork();
    if (pid > 0)
    {
        
    }
}
