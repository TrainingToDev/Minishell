/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:08:58 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 15:25:11 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        return (1);
    }
    return (0);
}

int wait_for_children(pid_t pid_left, pid_t pid_right, t_minishell *shell)
{
    int	status_left;
    int	status_right;

	status_left = 0;
	status_right = 0;
    waitpid(pid_left, &status_left, 0);
    waitpid(pid_right, &status_right, 0);
    if (WIFEXITED(status_right))
        shell->last_exit_status = WEXITSTATUS(status_right);
	else
        shell->last_exit_status = 1;
    return shell->last_exit_status;
}

pid_t fork_and_exec_left(t_ast *left, int pipefd[2], t_minishell *shell)
{
    pid_t	pid_left;

	pid_left = fork();
    if (pid_left == 0)
	{
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
            perror("dup2");
        close(pipefd[1]);
        exit(execute_ast(left, shell));
    }
	else if (pid_left < 0)
        perror("fork");
    return (pid_left);
}

pid_t fork_and_exec_right(t_ast *right, int pipefd[2], t_minishell *shell)
{
    pid_t	pid_right;

	pid_right = fork();
    if (pid_right == 0)
	{
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
            perror("dup2");
        close(pipefd[0]);
        exit(execute_ast(right, shell));
    } 
	else if (pid_right < 0)
        perror("fork");
    return (pid_right);
}

void close_pipe_descriptors(int pipefd[2])
{
    close(pipefd[0]);
    close(pipefd[1]);
}
