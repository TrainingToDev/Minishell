/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:01:27 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:51:06 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need amelioration


/* 
One global variable for signal

extern volatile sig_atomic_t g_signal_received; 

*/

void setup_signals(t_minishell *shell)
{
    if (shell->interactive)
    {
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, SIG_IGN);
    }
    else
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
    }
}

void signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signal_received = SIGINT;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
