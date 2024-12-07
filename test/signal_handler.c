/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-06 09:45:57 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-06 09:45:57 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler1(int signal, siginfo_t *info, void *content)
{
    (void)content;
    if (signal == SIGINT)
        g_sign = 1;
    if (signal == EOF)
        g_sign = 2;
    if (signal == )
        g_sign = 3;
}