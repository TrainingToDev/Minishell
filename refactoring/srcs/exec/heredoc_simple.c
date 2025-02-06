/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:21:17 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/27 21:21:34 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*transform(char *line, char *dlim, int qt, t_minishell *shell)
{
	char	*result;

	if (ft_strcmp(line, dlim) == 0)
	{
		free(line);
		return (NULL);
	}
	if (qt)
	{
		result = ft_strdup(line);
		free(line);
		return (result);
	}
	result = expand_var(line, shell);
	free(line);
	return (result);
}

void	heredoc_interactive(char *dlim, t_hdc *cnt, t_minishell *shell)
{
	char	*line;
	char	*expanded_line;
	char	*clean_delim;
	int		quoted;

	quoted = (dlim[0] == '\'' || dlim[0] == '\"');
	clean_delim = trim_quotes(dlim);
	if (!check_params(cnt, dlim, shell))
	{
		free(clean_delim);
		return ;
	}
	manage_heredoc();
	while (1)
	{
		line = read_user_input(clean_delim, shell);
		if (!line)
			break ;
		expanded_line = transform(line, clean_delim, quoted, shell);
		if (!expanded_line)
			break ;
		if (!insert_line(cnt, expanded_line))
			break ;
	}
	free(clean_delim);
}
