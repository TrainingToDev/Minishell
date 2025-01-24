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

static void freee(t_shell *shell, t_token **tok, int **fd)
{
    free_fd(fd);
    free_env(shell->env);
    free_exp(shell->exp);
    free_list(shell->built);
    free(shell);
    free_exec(tok);
}
static void execve_free(char **en, char **a, char *p)
{
    perror("execve");
    ft_free(en);
    ft_free(a);
    free(p);
    exit(1);
} 

static void for_parent(t_token **tok, t_shell *shell, int pid, char *p)
{
    waitpid(pid, NULL, 0);
    free(p);
    free_env(shell->env);
    free_exp(shell->exp);
    free_list(shell->built);
    free(shell);
    free_exec(tok);
}

int pipe_execve(t_token **tok,t_shell *shell, int id, int **fd)
{
    pid_t pid;
    char    *path;
    char    **arg;
    char    **en;

    path = get_path(&tok[id], shell->env);
    if (path == NULL)
        return(write(2, "command not found\n", 18));
    else
    {
        pid = fork();
        if (pid == 0)
        {
            en = form_env(shell->env, env_len(shell->env));
            arg = get_arg(tok[id], len_arg(tok[id]));
            freee(shell, tok, fd);
            if (execve(path, arg, en) < 0)
                execve_free(en, arg, path);
        }
        if ((pid > 0))
            for_parent(tok, shell, pid, path);
    }
    return (0);
}

void pipe_command(t_token **tok, t_shell *shell, int index, int **fd)
{
    int command_id;

    command_id = is_builtins(&tok[index], shell->built);
    if (command_id != 0)
    {
        printf ("builtins\n");
        take_all_quote(&tok[index]);
        exact_builtin(&tok[index], shell,command_id);
        free_ft(tok, shell);
    }
    else
    {
        printf ("execve pipe\n");
        pipe_execve(tok, shell, index, fd);
    }
}
