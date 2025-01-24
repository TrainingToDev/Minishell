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

//function specific for the piped(to do)

int **create_pipe(int nbr_pipe)
{
    int **pip;
    int i;

    if (nbr_pipe == 1)
        return (NULL);
    pip = (int**)malloc(sizeof(int*) * (nbr_pipe + 1));
    if (!pip)
        return (NULL);
    pip[0] = NULL; 
    i = 1;
    while (i < nbr_pipe)
    {
        pip[i] = (int *)malloc(sizeof(int) * 2);
        if (!pip[i])
            return (NULL);
        if ( pipe(pip[i]) == -1)
        {
            free_fd(pip);
            perror("pipe :");
            return (NULL);//free pip + perror
        }
        i++;
    }
    pip[i] = NULL;
    return (pip);
}
int dup_in(int **fd, int index)
{
    int state;

    state = 0;
    if (fd[index] != NULL)
    {
        close(fd[index][1]);
        if(dup2(fd[index][0], 0) == -1)
        {
            perror("dup2:");
            return (-1);
        }
        state = 1; 
    }
    return (state);

}

int dup_out(int **fd, int index)
{
    int state;

    state = 0;
    if (fd[index + 1] != NULL)
    {
        close(fd[index + 1][0]);
        if(dup2(fd[index + 1][1], 1)== -1)
        {
            perror("dup2:");
            return(-1);
        }
        state = 1;
    }
    return (state);
}

void child_routine(t_token **tok, int **fd, t_shell *shell, int index)
{
    int fd1;
    int fd2;

    fd1 = dup_in(fd, index);
    fd2 = dup_out(fd, index);
    if (fd1 < 0 || fd2 < 0)
    {
        perror("fd pipe:");
        free_ft(tok, shell);
        exit(1);
    }
    pipe_command(tok, shell, index, fd);
    if (fd1 == 1)
        close(fd[index][0]);
    if (fd2 == 1)
        close(fd[index + 1][1]);
}

void create_fork(t_token **tok, int nbr_pipe, t_shell *shell)
{
    int i;
    int *pid;
    int **fd;

    i = 0;
    pid = (int*)malloc(sizeof(int) * nbr_pipe);
    if (!pid)
        return ;
    fd = create_pipe(nbr_pipe);
    while(tok[i])
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            free(pid);
            child_routine(tok, fd, shell, i);
            free_fd(fd);
            exit (0);
        }
        else if (pid[i] > 0)
            waitpid(pid[i], NULL, 0);
        i++;
    }
    free_exec(tok);
    free(pid);
    free_fd(fd);
}
