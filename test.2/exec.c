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
int is_builtins(t_token **tok, t_list *built)
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
void exact_builtin(t_token **token, t_env *env, t_export *exp, int command_id)
{
    if (command_id == 1)
        echo_command(token);
    else if (command_id == 7)
        env_command(env, token);
    else if (command_id == 5)
        pwd_command(token);
    else if (command_id == 2)
        export_command(env, token, exp);
    else if (command_id == 3)
        unset_command(env, exp, token);
        /*
    else if (command_id == 6)
        //exit function;
    else if (command_id == 7)
        */
        //env function;
}

void pipe_implemantations(t_token **tok, int nbr_exc, t_list *built, t_env *env, t_export *exp)
{
    //int i;

    //i = 0;
    printf ("nbr_pipe : %i\n", nbr_exc);
    if (nbr_exc == 1)
        state_command(tok[0], built, env, exp);
    else
    {
        //pipe implementation
        create_fork(tok, nbr_exc, built, exp, env);
        printf ("pipe\n");
    }
}


void state_command(t_token *token, t_list *built, t_env *env, t_export *exp)
{
    int command_id;
 
    command_id = is_builtins(&token, built);
    if(command_id != 0)
    {
        take_all_quote(&token);
        printf("exec builtings\n");
        exact_builtin(&token, env, exp,command_id);
        free_token(token);
        //free all struct + handle signals
    }
    else
    {
        printf("fork and exec with execve\n");
        new_proc(&token, env, exp);
        //function that reformulate all the param (quote and form of param)
        //execve and recuperate the return of $? and  handle signals
    }
}

