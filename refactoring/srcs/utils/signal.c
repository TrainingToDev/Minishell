/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:02:59 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/06 17:21:07 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int g_check;

int	status_manager(int new_status, int mode)
{
	static int	status = SUCCESS;
	int temp;

	if (mode == STATUS_READ)
	{
		temp = status;
		status = SUCCESS;
		return (temp);
	}
	else if (mode == STATUS_WRITE)
	
		status = new_status;
	else if (mode == STATUS_INIT)
		status = SUCCESS;
	return (status);
}

static void	manager_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (1)
			return ;
		rl_redisplay();
		status_manager(128 + sig, STATUS_WRITE);
	}
}

static void	quit(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		status_manager(131, STATUS_WRITE);
	}	
}

void	setup_signals(void)
{
	signal(SIGINT, manager_signal);
	signal(SIGQUIT, SIG_IGN);
}

void setup_child(void)
{
	signal(SIGQUIT, quit);
}

static void	heredoc_signal(int sig)
 {
 	if (sig == SIGINT)
 	{
 		// ft_putendl_fd("", STDOUT_FILENO);
		g_check = 1;
 		status_manager(128 + sig, STATUS_WRITE);
 		// exit(128 + sig);
 	}

}

void	manage_heredoc(void)
{
	signal(SIGINT, heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
}

void reset_main(void)
{
	signal(SIGQUIT, SIG_IGN);
}
