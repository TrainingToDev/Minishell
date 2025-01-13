/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 08:08:41 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-13 08:08:41 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int all_num(char *in)
{
    int i;

    i = 0;
    while (in[i])
    {
        if (in[i] >= 48 && in[i] <= 57)
            i++;
        else if (in[i] == '=')
            i++;
        else
            return (1);
    }
    return (0);
}