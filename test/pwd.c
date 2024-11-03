/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:04:20 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 06:01:15 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd_command(t_parse *data)
{
    if (right_command(data->command, "pwd") != 1)
        return (0);
    if (data->option != NULL)
        return (0);//error no valid option
    else
    {
        printf("%s\n", getcwd(NULL, 0));
        return (1);
    }
}