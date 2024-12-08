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

    built = ft_lstnew("echo");
    ft_lstadd_back(&built, ft_lstnew("export"));
    ft_lstadd_back(&built, ft_lstnew("unset"));
    ft_lstadd_back(&built, ft_lstnew("cd"));
    ft_lstadd_back(&built, ft_lstnew("pwd"));
    ft_lstadd_back(&built, ft_lstnew("exit"));
    ft_lstadd_back(&built, ft_lstnew("env"));
    return (built);
}
static int is_builtins(t_token **tok, t_list *built)
{
    while ((*tok) && (*tok)->state != 1)
    {
        printf("here : %s -> %i\n", (*tok)->token, (*tok)->state);
        *tok = (*tok)->next;
    }
    while (built)
    {
        if (ft_strncmp((*tok)->token, built->content, ft_strlen((*tok)->token)) == 0)
        {
            return (1);
            printf ("builtins\n");
        }
        built = built->next;
    }
    return (0);
}


void state_command(t_token **token, int pipe, t_list *built)
{
    if (pipe == 1)
    {
        if(is_builtins(token, built) == 1)
        {
            //function exec_builtings
            printf("exec builtings\n");
        }
        else
        {
            //function exec_all
            printf("fork and exec with execve\n");
        }
    }
    else
    {
        //pipe implementation
        printf ("pipe\n");
    }
}