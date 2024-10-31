/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:21:52 by miaandri          #+#    #+#             */
/*   Updated: 2024/10/31 13:17:02 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void    echo_command(char *input)//atao int ity de miretourne 1 (vrai) et 0 (faux)
{
    char *command;
    char *option;
    char *string;

    command = get_command(input);
    option = get_option(input);
    if (option == NULL)
    {
        free(command);
        free(input);
        return ;
    }   
    string = get_string(input, (ft_strlen(command) - 1), (ft_strlen(option)));
    if (!string)
    {
        free(command);
        free(option);
        free(input);
        return ;
    }
    printf("%s", string);
    free(command);
    free(option);
    free(string);
    free(input);
}

