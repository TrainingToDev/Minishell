/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:24:57 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/08 08:15:42 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_heredoc(t_hdc *cnt, char *dlim, t_minishell *shell, int c)
{
	manage_heredoc();
	if (c)
		heredoc_copied(cnt, dlim, shell);
	else
		heredoc_interactive(dlim, cnt, shell);
	exit(0);
}

static int	parent_heredoc(pid_t pid, t_minishell *shell)
{
	int exit_status;

	del();
	waitpid(pid, &shell->last_exit_status, 0);
	reset_main();
	if (WIFSIGNALED(shell->last_exit_status))
		exit_status = 128 + WTERMSIG(shell->last_exit_status);
	else
		exit_status = WEXITSTATUS(shell->last_exit_status);
	status_manager(exit_status, STATUS_WRITE);
	return (exit_status);
}

int	forked_heredoc(t_hdc *cnt, char *dlim, t_minishell *shell, int c)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_heredoc(cnt, dlim, shell, c);
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	return (parent_heredoc(pid, shell));
}
