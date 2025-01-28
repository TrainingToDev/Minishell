/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plou.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 01:56:35 by herandri          #+#    #+#             */
/*   Updated: 2025/01/23 23:37:10 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status_manager(int new_status, int mode)
{
	static int	status;

	status = 0;
	if (mode == STATUS_READ)
		return status;
	else if (mode == STATUS_WRITE)
		status = new_status;
	return (status);
}

static void	setup_signal(int signum, void (*signal_handler)(int))
{
	struct sigaction	action;

	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(signum, &action, NULL);
}

void	reset_prompt(int sig)
{
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	status_manager(128 + sig, STATUS_WRITE);
}

void	main_signals(void)
{
	setup_signal(SIGINT, reset_prompt);
	setup_signal(SIGQUIT, SIG_IGN);
}

void	child_signal(int sig)
{
	if (sig == SIGINT)
		ft_putendl_fd("", STDOUT_FILENO);
	else if (sig == SIGQUIT)
		ft_putendl_fd("Quit", STDOUT_FILENO); 
}

void	manage_child(void)
{
	setup_signal(SIGINT, child_signal);
	setup_signal(SIGQUIT, child_signal); 
}

void	heredoc_signal(int sig)
{
	if (sig == SIGINT) // CTRL+C
    {
        ft_putendl_fd("", STDOUT_FILENO);
        status_manager(130, STATUS_WRITE);
        exit(130);
    }
}

void	manage_heredoc(void)
{
	setup_signal(SIGINT, heredoc_signal);
	setup_signal(SIGQUIT, SIG_IGN);
}

// void	main_heredoc(void)
// {
// 	setup_signal(SIGINT, SIG_IGN);
// 	setup_signal(SIGQUIT, SIG_IGN);
// }

