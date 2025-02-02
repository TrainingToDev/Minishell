/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:58:06 by herandri          #+#    #+#             */
/*   Updated: 2025/02/01 23:42:18 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_builtins_redir(t_redir *redirs, t_minishell *shell)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (current->type == REDIR_IN)
		{
			if (process_redir_in(current, 0) == -1)
				return -1;
		}
		else if (current->type == REDIR_HEREDOC)
		{
			if (process_heredoc(current, shell, 0) == -1)
				return -1;
		}
		else if (current->type == REDIR_OUT)
		{
			if (process_redir_out(current, 1) == -1)
				return -1;
		}
		else if (current->type == REDIR_APPEND)
		{
			if (process_redir_append(current, 1) == -1)
				return -1;
		}
		current = current->next;
	}
	return 0;
}
