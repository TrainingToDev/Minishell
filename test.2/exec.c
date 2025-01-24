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
int is_builtins(t_token **tok, t_list *b)
{
    int count;
    t_list *built;

    count = 1; 
    built = b;
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
        }
        count++;
        built = built->next;
    }
    return (0);
}
void exact_builtin(t_token **token,t_shell *shell, int command_id)
{
    if (command_id == 1)
        echo_command(token);
    else if (command_id == 7)
        env_command(shell->env, token);
    else if (command_id == 5)
        pwd_command(token);
    else if (command_id == 2)
        export_command(shell->env, token, shell->exp);
    else if (command_id == 3)
        unset_command(shell->env, shell->exp, token);
        /*
    else if (command_id == 6)
        //exit function;
    else if (command_id == 7)
        */
        //env function;
}

void pipe_implemantations(t_token **tok, int nbr_exc, t_shell *shell)
{
    printf ("nbr pile d'exec : %i\n", nbr_exc);
    if (nbr_exc == 1)
        state_command(tok, shell);
    else
    {
        printf ("pipe\n");
        create_fork(tok, nbr_exc, shell);
    }
}


void state_command(t_token **token, t_shell *shell)
{
    int command_id;
 
    command_id = is_builtins(&token[0], shell->built);
    if(command_id != 0)
    {
        printf("exec builtings\n");
        take_all_quote(&token[0]);
        exact_builtin(&token[0], shell, command_id);
        free_exec(token);
    }
    else
    {
        printf("fork and exec with execve\n");
        new_proc(token, shell);
        //function that reformulate all the param (quote and form of param)
        //execve and recuperate the return of $? and  handle signals
    }
}

