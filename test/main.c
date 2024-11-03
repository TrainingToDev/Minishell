/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:49:54 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 05:34:26 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main (void)
{
    char *input;
    int state;//atao eo @ env iny ilay ?
    t_parse *data;

    while (1)
    {
        input = readline("minishell:");
        data = get_struct(input);
        if (echo_command(data) == 1)
            state = 1;
        else if (pwd_command(data) == 1)
            state = 1;
        
    }
    free (input);
}