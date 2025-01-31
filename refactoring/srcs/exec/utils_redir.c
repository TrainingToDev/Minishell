/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:07 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 16:14:25 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_pipe(t_redir *cur)
{
	int		pipefd[2];
	size_t	i;
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	i = 0;
	while (i < cur->content->count)
	{
		line = cur->content->lines[i];
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		i++;
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}

int	heredoc_redir(t_redir *current, t_minishell *shell)
{
	if (!current->content)
	{
		printf("minishell: HEREDOC : contenu invalide ou NULL\n");
		return (-1);
	}
	if (current->content->count > 0)
	{
		heredoc_copied(current->content, current->filename, shell);
		return(0);
	}
	else
	{
		heredoc_interactive(current->filename, current->content, shell);
		return(0);
	}
	return (heredoc_pipe(current));
}
