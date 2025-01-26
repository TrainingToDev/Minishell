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

static int setup_heredoc_content_pipe(t_redir *current)
{
    int		pipefd[2];
    size_t	i;

    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        return (-1);
    }
    i = 0;
    while (i < current->content->count)
	{
        write(pipefd[1], current->content->lines[i], ft_strlen(current->content->lines[i]));
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

int handle_redir_heredoc(t_redir *current, t_minishell *shell)
{
    if (!current->content)
	{
        fprintf(stderr, "minishell: HEREDOC : contenu invalide ou NULL\n");
        return (-1);
    }
    if (current->content->count > 0)
        handle_copied_heredoc(current->content, current->filename, shell);
    else
        handle_interactive_heredoc(current->filename, current->content, shell);
    return (setup_heredoc_content_pipe(current));
}

