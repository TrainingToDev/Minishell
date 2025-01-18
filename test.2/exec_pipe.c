/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-18 13:56:59 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-18 13:56:59 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//should built one big struct to contain t_env, t_exp, t_list

//static void for_parent()

int pipe_execve(t_token **tok, t_env *env)
{
    pid_t pid;
    char    *path;
    char    **arg;
    char    **en;

    path = get_path(tok, env);
    arg = get_arg(tok, len_arg(*tok));
    en = form_env(env, env_len(env));
    if (path == NULL)
        return(write(2, "command not found\n", 18));
    else
    {
        pid = fork();
        if (pid == 0)
        {
            if (execve(path, arg, en) < 0)
            {
                perror("execve:");
                exit (1);
            }
        }
        if (pid > 0)
            
    }
    return (0);
}




void pipe_command(t_token *tok, t_list *lst, t_env *env, t_export *exp)
{
    int command_id;

    command_id = is_builtins(&tok, lst);
    if (command_id != 0)
    {
        take_all_quote(&tok);
        exact_builtin(&tok, env, exp, command_id);
    }
    else
    {

    }
}