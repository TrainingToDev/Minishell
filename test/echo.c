/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:21:52 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/02 10:38:45 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        printf("%s", data->param);
        return (1);   
    }
    return (0);
}

