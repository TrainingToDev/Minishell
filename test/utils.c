/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:24:45 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/02 15:20:11 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  get_len(char **dest)
{
    int i;

    i = 0;
    while(dest[i])
        i++;
    return (i);
}

void	ft_free(char **dest)
{
    int len;
    
	len = get_len(dest);
    while (0 < len)
	{
        if (*dest + len)
        {
    		free (*dest + len);
        }
		len--;
	}
	free(dest);
}

int right_command(char *data, char *command)
{
    int len;

    len = ft_strlen(command);
    while (len > 0)
    {
        if (data[len] != command[len])
            return (0);
        len--;
    }
    return (1);
}

int is_alpha(int c)
{
    if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97))
        return (1);
    return (0);
}
