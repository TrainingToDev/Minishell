/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:24:45 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 11:18:56 by miaandri         ###   ########.fr       */
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

int exact_command(char *data, char *command)
{
    int i;

    i = 0;
    if (ft_strlen(data) != ft_strlen(command))
    {
       // printf("%i->%i\n", (int)ft_strlen(data) , (int)ft_strlen(command));   
        return (0);
    }
    while (data[i])
    {
        if (data[i] != command[i])
            return (0);
        i++;
    }    
    return (1);
}

int is_alpha(int c)
{
    if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97))
        return (1);
    return (0);
}
