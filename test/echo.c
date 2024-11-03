/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:21:52 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 06:00:57 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_echo(char *string)
{
    int i;

    i = 0;
    while (string[i])
    {
        if (string[i] == ' ' && string[i + 1] == ' ')
            i++;
        else if (string[i] == '"' )//mbola misy ilay otran'zao 'iayiluyafyf'
        {
            i++;
            while(string[i] != '"')
            {
                printf("%c", string[i]);
                i++;
            }
        }
        else
             printf("%c", string[i]);
        i++;
    }
}

int    echo_command(t_parse *data)
{
    if (right_command(data->command, "echo") != 1)
        return (0);
    if (right_command(data->option, "-n") != 1)
        return (0);
    if (data->param == NULL)
        return (1);
    else
    {
        print_echo(data->param);
        return (1);   
    }
    return (0);
}

