/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:30:47 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/18 16:29:23 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *g_token(char *token)
{
    t_token *list;

    if (!token)
        return (NULL);
    list = (t_token *)malloc(sizeof(t_token));
    if (!list)
        return (NULL);
    list->token = ft_strdup(token);
    list->state = 0;
    list->check = 0;
    list->next = NULL;
    return (list);
}

static t_token *last_token(t_token *tok)
{
    while (tok->next != NULL)
        tok = tok->next;
    return (tok);
}

void    add_new_token(t_token **tok, t_token *new)
{
    if (!tok || !new)
        return ;
    if (*tok != NULL)
        last_token(*tok)->next = new;
    else
        *tok = new;       
}