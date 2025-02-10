/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:31:57 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/01 23:42:41 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int heredoc_redir(t_redir *redirs, t_minishell *shell, int mode, int f)
{
	t_redir *current;

	current = redirs;
	while (current)
	{
		if (current->type == REDIR_HEREDOC)
		{
			if (process_heredoc(current, shell, mode, f) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	apply_redir(t_redir *redirs, t_minishell *shell, int mode, int f)
{
	t_redir	*current;

	if (heredoc_redir(redirs, shell, mode, f) == -1)
		return (-1);
    current = redirs;
    while (current)
    {
        if (current->type == REDIR_OUT)
        {
            if (process_redir_out(current, mode) == -1)
                return (-1);
        }
        else if (current->type == REDIR_APPEND)
        {
            if (process_redir_append(current, mode) == -1)
                return (-1);
        }
        else if (current->type == REDIR_IN)
        {
            if (process_redir_in(current, mode) == -1)
                return (-1);
        }
        current = current->next;
    }
    return (0);
}

int open_input(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
		{
			print_error(E_CMD, filename, ERR_G);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		}
		else if (errno == EACCES)
		{
			print_error(E_CMD, filename, ERR_G);
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
		}
		else
		{
			print_error(E_CMD, filename, ERR_G);
			ft_putendl_fd(": error Unknown", STDERR_FILENO);
		}
		return (-1);
	}
	return (fd);
}
