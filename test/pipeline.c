/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-27 08:13:40 by miaandri          #+#    #+#             */
/*   Updated: 2024-11-27 08:13:40 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_pipe(t_token **all)
{
    int i;

    i = 0;
    while (all[i])
        i++;
    if (i == 1)
        return (0);
    return (i);
}

void routine_test(int i)
{
    printf("i ' m :%i\n", i);
    usleep(20);
}


void    create_fils(t_token **all, int pipe_nbr)
{
    pid_t   pid;
    int i;

    i = 0;
    (void)all;
    printf ("here %i\n", pipe_nbr);
    if (pipe_nbr == 0)
    {
        printf ("one proc\n");
        return;
    }
    while (i < pipe_nbr)
    {
        printf("in\n");
        pid = fork();
        printf("pid : %i\n", (int)pid);
        if (pid == -1)
        {
            perror("pipe");
            return ;
        }
        else if (pid > 0)
        {
            printf("here2\n");
            printf("pid in: %i\n", (int)pid);
            routine_test(i);
        }
        kill(pid, SIGKILL);
        i++;
    }
        

}
