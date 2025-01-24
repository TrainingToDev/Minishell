/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fuction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 06:56:51 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-13 06:56:51 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void ft_free(char **splitted)
{
    int len;

    len = 0;
    while (splitted[len])
        len++;
    while(len >= 0)
    {
        free(splitted[len]);
        len--;
    }
    free (splitted);
}

void free_token (t_token *tok)//free on token list but not the array of token
{
    t_token *tmp;
    t_token *cur;

    tmp = tok;
    while (tmp)
    {
        cur = tmp->next;
        free (tmp->token);
        free (tmp);
        tmp = NULL;
        tmp = cur;
    }
    tok = NULL;
}

void free_env(t_env *env)
{
    t_env *tmp;
    t_env   *cur;

    tmp = env;
    while (tmp)
    {
        cur = tmp->next;
        free(tmp->var);
        free(tmp->value);
        free(tmp);
        tmp = NULL;
        tmp = cur;
    }
    env = NULL;
}

void free_exp(t_export *env)
{
    t_export *tmp;
    t_export *cur;

    tmp = env;
    while (tmp)
    {
        cur = tmp->next;
        free(tmp->proto);
        free(tmp->var);
        free(tmp->value);
        free(tmp);
        tmp = NULL;
        tmp = cur;
    }
    env = NULL;
}

void free_fd(int **fd)
{
    int i;

    i = 1;
    while (fd[i])
    {
        free(fd[i]);
        i++;
    }
    free (fd);
}

void free_exec(t_token **tok)
{
    int i;

    i = 0;
    while (tok[i])
    {
        free_token(tok[i]);
        i++;
    }
    free(tok);
}

void free_list(t_list *list)
{
    t_list *tmp;
    t_list *cur;

    tmp = list;
    while (tmp)
    {
        cur = tmp->next;
        free(tmp);
        tmp = NULL;
        tmp = cur;
    }
    list = NULL;
}

void free_ft(t_token **tok, t_shell *shell)
{
    free_env(shell->env);
    free_exp(shell->exp);
    free_list(shell->built);
    free(shell);
    free_exec(tok);
}