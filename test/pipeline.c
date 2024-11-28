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
/*
void routine_test(t_token *token)
{
    usleep(20);
}
*/


void    create_fils(t_token **all, int pipe_nbr)
{
    pid_t   pid[2];
    int pipe_fd[2];
  //  int i;

    //i = 0;
    (void)all;
    if (pipe_nbr == 0)
    {
        printf ("one proc\n");
        return;
    }
    /*
    while (i < pipe_nbr)
    {
        pid[0] = fork();
        pid[1] = fork();
        printf("pid : %i\n", (int)pid[0]);
        printf("pid : %i\n", (int)pid[0]);
        kill(pid[1], SIGKILL);
        kill(pid[0], SIGKILL);
       if (pid[0] > 0)
        {

        }
      i++;
    }
    */
   /*

    pid_t   pid[nb_command];
    int pipe_fd[nb_command - 1][2];
    [
        [0,1],
        [0,1],
        [0,1]
    ]
   */
  i = ++;
   else
   {
        /*
        pipe_fd 1
        */
        pid[i] = fork();
        /*
            comm : pipe_fd 1
        */

        pid[i + 1] = fork();
        /*
            comm : pipe_fd 1
        */

        printf("pid : %i\n", (int)pid[0]);
        printf("pid : %i\n", (int)pid[0]);
        if (pipe(pipe_fd) == -1)
        {
            printf ("error pipe\n");
            return ;
        }
        printf ("fd : %i\n", pipe_fd[0]);
        printf ("fd1 : %i\n", pipe_fd[1]);
        if (pipe(pipe_fd) == -1)
        {
            printf ("error pipe\n");
            return ;
        }
        printf ("fd2 : %i\n", pipe_fd[0]);
        printf ("fd2 : %i\n", pipe_fd[1]);
        /*
        if (pid[0] > 0 && pid[1] > 0)
        {

        }
        */
        kill(pid[1], SIGKILL);
        kill(pid[0], SIGKILL);
   }


}
