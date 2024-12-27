/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-06 09:54:42 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-06 09:54:42 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *get_all_builtins()
{
    t_list *built;

    built = ft_lstnew("echo");//1
    ft_lstadd_back(&built, ft_lstnew("export"));//2
    ft_lstadd_back(&built, ft_lstnew("unset"));//3
    ft_lstadd_back(&built, ft_lstnew("cd"));//4
    ft_lstadd_back(&built, ft_lstnew("pwd"));//5
    ft_lstadd_back(&built, ft_lstnew("exit"));//6
    ft_lstadd_back(&built, ft_lstnew("env"));//7
    return (built);
}
static int is_builtins(t_token **tok, t_list *built)
{
    int count;

    count = 1; 
    while ((*tok) && (*tok)->state != 1)
    {
        printf("here : %s -> %i\n", (*tok)->token, (*tok)->state);
        *tok = (*tok)->next;
    }
    while (built)
    {
        if (ft_strncmp((*tok)->token, built->content, ft_strlen(built->content)) == 0)
        {
            return (count);
            //printf ("builtins\n");
        }
        count++;
        built = built->next;
    }
    return (0);
}
static void exact_builtin(t_token **token, t_env *env, int command_id)
{
    if (command_id == 1)
        echo_command(token);
    else if (command_id == 7)
        env_command(env, token);
    else if (command_id == 5)
        pwd_command(token);
        /*
    else if (command_id == 4)
        //cd function;
    else if (command_id == 5)
        //pwd function;
    else if (command_id == 6)
        //exit function;
    else if (command_id == 7)
        */
        //env function;
}

void state_command(t_token **token, int pipe, t_list *built, t_env *env)
{
    int command_id;
    (void)env;
 
    if (pipe == 1)
    {
        command_id = is_builtins(token, built);
        if(command_id != 0)
        {
            take_all_quote(token);
            printf("exec builtings\n");
            exact_builtin(token, env, command_id);
            //free all struct + handle signals
        }
        else
        {
            printf("fork and exec with execve\n");
            get_all_path(env);
            //function that reformulate all the param (quote and form of param)
            //execve and recuperate the return of $? and  handle signals
        }
    }
    else
    {
        //pipe implementation
        printf ("pipe\n");
    }
}