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

    tmp = tok->next;
    while (tmp)
    {
        free (tok->token);
        free (tok);
        tok = tmp;
        tmp = tmp->next;
    }
}

void free_env(t_env *env)
{
    t_env *tmp;

    tmp = env->next;
    while (tmp)
    {
        free(env->var);
        free(env->value);
        free(env);
        env = tmp;
        tmp = tmp->next;
    }
}
