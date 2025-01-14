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
