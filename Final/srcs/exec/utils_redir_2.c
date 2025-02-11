/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:10:33 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/09 20:34:46 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redir_in(t_redir *current)
{
	int	fd;

	fd = open(current->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(current->filename);
		status_manager(1, STATUS_WRITE);
		return (-1);
	}
    if (dup2(fd ,STDIN_FILENO) == -1)
    {
        print_error(E_DUPFD, current->filename, ERR_G);
        close(fd);
        return (-1);
    }
	close(fd);
	return (0);
}

int redir_out(t_redir *current)
{
	int	fd;

	fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(E_CMD, current->filename, ERR_G);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (-1);
	}
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        print_error(E_DUPFD, current->filename, ERR_G);
        close(fd);
        return (-1);
    }
	close(fd);
	return (0);
}

int	redir_append(t_redir *current)
{
	int	fd;

	fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(E_CMD, current->filename, ERR_G);
		return (-1);
	}
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        print_error(E_DUPFD, current->filename, ERR_G);
        close(fd);
        return (-1);
    }
	close(fd);
	return (0);
}


int heredoc(t_redir *cur, t_minishell *shell)
{
	int ret;

	if (!cur->content)
	{
		print_error(E_NOMEM, "HEREDOC: invalid content", ERR_SEGV);
		return (-1);
	}
	if (cur->content->count > 0)
		ret = forked_heredoc(cur->content, cur->filename, shell, 1);
	else
		ret = forked_heredoc(cur->content, cur->filename, shell, 0);
	return (ret);
}
