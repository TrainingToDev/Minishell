/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-27 11:15:53 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-27 11:15:53 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//if pid != 0: process parent
//if pid == 0: process child
#include "minishell.h"

static int command_not_found(t_token **tok)
{
    write(2, "command not found\n", 18);
    free_exec(tok);
    return (127);//command not found
}
static void exec_free(char **en, char **arg, char *p)
{
    perror("execve:");
    ft_free(en);
    ft_free(arg);
    free(p);
    exit (1);
}
static void free_ex(t_token **t, t_shell *shell)
{
    free_exec(t);
    free_env(shell->env);
    free_exp(shell->exp);
    free_list(shell->built);
    free(shell);

}

static void new_proc2(t_token **tok, int pid, char *path)
{
    waitpid(pid, NULL, 0);
    free (path);
    free_exec(tok);
}

int new_proc(t_token **tok, t_shell *shell)//execve pour nbr de pile d'exec == 1
{
    pid_t pid;
    char *path;
    char **arg;
    char **en;

    path = get_path(&tok[0], shell->env);
    if (path == NULL)
        return (command_not_found(&tok[0]));
    pid = fork();
    if (pid == 0)
    {
        arg = get_arg((*tok), len_arg(*tok));
        en = form_env(shell->env, env_len(shell->env));
        free_ex(tok, shell);
        if (execve(path, arg, en) < 0)
            exec_free(en, arg, path);
    }
    if (pid > 0)
        new_proc2(tok, pid, path);
    return (0);
}
