/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:07 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/01 23:44:15 by herandri         ###   ########.fr       */
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
		perror("pipe failed");
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

int	process_heredoc(t_redir *cur, t_minishell *shell, int mode)
{
	if (!cur->content)
	{
		printf("minishell: HEREDOC: contenu invalide ou NULL\n");
		return (-1);
	}
	if (cur->content->count > 0)
		heredoc_copied(cur->content, cur->filename, shell);
	else
		heredoc_interactive(cur->filename, cur->content, shell);
	if (mode)
		return (heredoc_pipe(cur));
	else
		return (0);
}
