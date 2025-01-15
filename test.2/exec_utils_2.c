/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-15 07:30:45 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-15 07:30:45 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *reform_simple(char *tok)//get_off the '>' or '<' 
{
    char *new;
    int i;

    tok = get_off_quote(tok, count_quote(tok));
    new = (char *)malloc(sizeof(char) * ft_strlen(tok));
    if (!new)
        return (NULL);
    i = 1;
    while (tok[i])
    {
        new[i - 1] = tok[i];
        i++;
    }
    new[i - 1] = '\0';
    free (tok);
    return (new);
}

char *reform_double(char *tok)//get_off the ">>" or "<<"
{
    char *new;
    int i;

    tok = get_off_quote(tok, count_quote(tok));
    new = (char *)malloc(sizeof(char) * (ft_strlen(tok) - 1));
    if (!new)
        return (NULL);
    i = 2;
    while (tok[i])
    {
        new[i - 2] = tok[i];
        i++;
    }
    new[i - 2] = '\0';
    free (tok);
    return (new);
}