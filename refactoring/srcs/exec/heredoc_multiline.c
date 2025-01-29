/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_multiline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:21:17 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/27 21:19:42 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_line(t_hdc *cnt, size_t i, int qt, t_minishell *shell)
{
	char	*expanded_line;

	if (qt)
		expanded_line = ft_strdup(cnt->lines[i]);
	else
		expanded_line = expand_variables_in_str(cnt->lines[i], shell);
	if (!expanded_line)
	{
		perror("expand_variables_in_str");
		return (0);
	}
	free(cnt->lines[i]);
	cnt->lines[i] = expanded_line;
	return (1);
}

static int	expand_and_update(t_hdc *cnt, int qt, t_minishell *shell)
{
	char	*clean_delim;
	size_t	i;

	if (!cnt || !cnt->lines || cnt->count == 0)
		return (0);
	clean_delim = trim_quotes(cnt->lines[cnt->count - 1]);
	i = 0;
	while (i < cnt->count)
	{
		if (i == cnt->count - 1
			&& ft_strcmp(cnt->lines[i], clean_delim) == 0)
		{
			i++;
			continue ;
		}
		if (!update_line(cnt, i, qt, shell))
		{
			free(clean_delim);
			return (0);
		}
		i++;
	}
	free(clean_delim);
	return (1);
}

static int	read_expand(t_hdc *cnt, char *dlim, t_minishell *shell)
{
	char	*expanded_line;
	char	*line;

	while (1)
	{
		line = read_user_input(dlim, shell);
		if (!line)
			break ;
		if (ft_strcmp(line, dlim) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = expand_variables_in_str(line, shell);
		free(line);
		if (!expanded_line)
			return (0);
		if (!insert_line(cnt, expanded_line))
		{
			free(expanded_line);
			return (0);
		}
	}
	return (1);
}

static void	clean_delimiter(t_hdc *cnt, char *dlim)
{
	char	*clean_delim;

	clean_delim = trim_quotes(dlim);
	if (cnt->count > 0
		&& ft_strcmp(cnt->lines[cnt->count - 1], clean_delim) == 0)
	{
		free(cnt->lines[cnt->count - 1]);
		cnt->lines[cnt->count - 1] = NULL;
		cnt->count--;
	}
	free(clean_delim);
}

void	heredoc_copied(t_hdc *cnt, char *dlim, t_minishell *shell)
{
	char	*clean_delim;
	int		qt;

	if (!check_params(cnt, dlim, shell))
		return ;
	qt = (dlim[0] == '\'' || dlim[0] == '\"');
	clean_delim = trim_quotes(dlim);
	// manage_heredoc(); // signal
	if (!expand_and_update(cnt, qt, shell))
	{
		free(clean_delim);
		return ;
	}
	if (cnt->count == 0
		|| ft_strcmp(cnt->lines[cnt->count - 1], clean_delim) != 0)
	{
		if (!read_expand(cnt, clean_delim, shell))
		{
			free(clean_delim);
			return ;
		}
	}
	clean_delimiter(cnt, clean_delim);
	free(clean_delim);
}
