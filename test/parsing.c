/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:25:54 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/11 14:37:25 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_split(char **data , int len)
{
    while (0 < len)
    {
        free(*data + len);
        len--;
    }
    free(data);
}


t_parse **get_data(char *input, int len)//free @ fin de readline anakiray
{
    t_parse **data;
    char **temp;
    int i;
    
    data = (t_parse**)malloc(sizeof(t_parse *) * len );
    if (!data)
        return (NULL);
    i = 0;
    if (len == 1)
    {
        temp[0] = get_struct(input);
        return (data);
    }
    temp = ft_split(input, '|');
    while (temp[i])
    {
        data[i] = get_struct(temp[i]);
        i++;
    }
    free_split(temp, len + 1);
    return (data);
}