/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:02:59 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/29 02:04:06 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status_manager(int new_status, int mode)
{
	static int	status;

	status = 0;
	if (mode == STATUS_READ)
		return (status);
	else if (mode == STATUS_WRITE)
		status = new_status;
	return (status);
}

int	is_heredoc(int set_mode)
{
	static int	heredoc_mode = 0;

	if (set_mode != -1)
		heredoc_mode = set_mode;
	return (heredoc_mode);
}

static void	manager_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		if (is_heredoc(-1) == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		status_manager(128 + sig, STATUS_WRITE);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, manager_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		status_manager(130, STATUS_WRITE);
		exit(130);
	}
}

void	manage_heredoc(void)
{
	signal(SIGINT, heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
}
