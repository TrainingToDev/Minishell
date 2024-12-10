/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:02:59 by miaandri          #+#    #+#             */
/*   Updated: 2024/12/08 09:27:41 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int **create_pipe(int nbr_pipe)
{
    int **pip;
    int i;

    if (nbr_pipe == 1)
        return (NULL);
    pip = (int**)malloc(sizeof(int*) * nbr_pipe + 1);
    if (!pip)
        return (NULL);
    pip[0] = NULL; 
    i = 1;
    while (i <= nbr_pipe)
    {
        pip[i] = (int *)malloc(sizeof(int) * 2);
        if (!pip[i])
            return (NULL);//free pip + perror
        if ( pipe(pip[i]) == -1)
            return (NULL);//free pip + perror
        /*
        else
        {
            printf ("fd r: %i\n", pip[i][0]);
            printf ("fd w: %i\n", pip[i][1]);
        }
        */
        i++;
    }
    pip[i] = NULL;
    return (pip);
}
void dup_for_kids(int **fd, int index)
{
    if (fd[index] != NULL)
    {
        close(fd[index][1]);
        if(dup2(fd[index][0], 0) == -1)
            return;
        close(fd[index][0]);
    }
    if (fd[index + 1] != NULL)
    {
        close(fd[index][0]);
        if(dup2(fd[index][1], 1)== -1)
            return;
        close(fd[index][1]);
    }
}

void create_fork(t_token **tok, int **fd, int nbr_pipe, t_list *list)
{
    int i;
    int *pid;

    i = 0;
    pid = (int*)malloc(sizeof(int) * nbr_pipe);
    if (!pid)
        return ;
    while(tok[i])
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            dup_for_kids(fd, i);
            state_command(&tok[i], nbr_pipe, list);
            //fils routine
        }
        else if (pid[i] > 0)
        {
            //pere routine
            //waitpid(pid[i], NULL, 0);
            printf("parent\n");
            exit (0);
        }
        i++;
    }
}