/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:49:54 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/02 16:02:06 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main (void)
{
    char *input;
    t_parse *data;

    while (1)
    {
        input = readline("minishell:");
        data = get_struct(input);
        //echo_command(data);
    }
    free (input);
}