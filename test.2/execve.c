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

char *real_dir(char **path, char *cmd)//if null command not found so->$? = 127
{
    int i;
    char *dir;
    struct stat buf;

    i = 0;
    while (path[i])
    {
        dir = ft_strjoin(path[i], cmd);//cmd = /command
        if (stat(dir, &buf) == 0)
        {
            if (S_ISREG(buf.st_mode) == 1)
            {
                free(cmd);
                ft_free(path);
                return (dir);
            }
        }
        free(dir);
        i++;
    }
    free(cmd);    
    ft_free(path);
    return (NULL);
}

static int is_absolute(char *cmd)// 1 == absolute path + state
{
    struct stat buf;

    if (ft_strchr(cmd, '/') != NULL)
    {
        if (stat(cmd, &buf) == 0)
        {
            if (S_ISREG(buf.st_mode) == 1)
                return (1);
        }
        else
            return (0);
    }
    return (0);
}

static char *get_path(t_token **token, t_env *env)
{
    t_token *tmp;
    char **path;
    char *cmd;

    tmp = (*token);
    while (tmp->state != 1)
        tmp = tmp->next;
    if (is_absolute(tmp->token) == 1)
    {
        printf ("is_absolute command\n");
        return (ft_strdup(tmp->token));
    }
    path = get_all_path(env);
    cmd = ft_strjoin("/", tmp->token);
    return (real_dir(path, cmd));
}

static int env_len(t_env *env)
{
    t_env *tmp;
    int len;
    
    tmp = env;
    len = 0;
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }
    return (len);
}
char **form_env(t_env *env, int len)
{
    t_env *tmp;
    char **en;
    int i;

    tmp = env;
    i = 0;
    en = (char **)malloc(sizeof(char*) * len + 2);
    if (!en)
        return (NULL);
    while (i < len)
    {
        en[i] = ft_strjoin(tmp->var, tmp->value);
        printf ("env : %s\n", en[i]);
        i++;
        tmp = tmp->next;
    }
    en[i] = "\0";
    return (en);
}

int new_proc(t_token **tok, t_env *env)//+ free t_token + free t_env
{
    pid_t pid;
    char *path;
    char **arg;
    char **en;

    pid = fork();
    if (pid > 0)
    {
        path = get_path(tok, env);
        printf ("%s\n", path);
        if (path == NULL)
        {
            write(2, "command not found\n", 18);
            return (127);//$? command not found
        }
        arg = get_arg((*tok), len_arg(*tok));
        en = form_env(env, env_len(env));
        kill(pid, SIGKILL);//temporary
    }
    return (0);
}
