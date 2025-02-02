/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:02:59 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/29 02:03:44 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_heredoc_content(t_hdc *cnt)
{
	size_t	i;

	if (!cnt || !cnt->lines)
		return ;
	i = 0;
	while (i < cnt->count)
	{
		free(cnt->lines[i]);
		i++;
	}
	free(cnt->lines);
	cnt->lines = NULL;
	cnt->count = 0;
}

t_hdc	*init_heredoc(void)
{
	t_hdc	*cnt;

	cnt = malloc(sizeof(t_hdc));
	if (!cnt)
		return (NULL);
	cnt->lines = NULL;
	cnt->count = 0;
	return (cnt);
}

char	**split_lines(char *input)
{
	char	**lines;

	lines = ft_split(input, '\n');
	if (!lines)
		return (NULL);
	return (lines);
}

static char	**dup_lines(t_hdc *cnt, char *line)
{
	char	**new_lines;
	size_t	j;

	new_lines = malloc(sizeof(char *) * (cnt->count + 1));
	if (!new_lines)
		return (NULL);
	j = 0;
	while (j < cnt->count)
	{
		new_lines[j] = cnt->lines[j];
		j++;
	}
	free(cnt->lines);
	new_lines[cnt->count] = ft_strdup(line);
	if (!new_lines[cnt->count])
	{
		while (j-- > 0)
			free(new_lines[j]);
		free(new_lines);
		return (NULL);
	}
	return (new_lines);
}

int	add_line(t_hdc *cnt, char *line)
{
	char	**new_lines;

	new_lines = dup_lines(cnt, line);
	if (!new_lines)
		return (-1);
	cnt->lines = new_lines;
	cnt->count++;
	return (0);
}

int	get_lines(t_hdc *cnt, char **lines, char *dlim)
{
	size_t	i;

	i = 1;
	while (lines[i])
	{
		if (add_line(cnt, lines[i]) == -1)
		{
			free_heredoc_content(cnt);
			return (-1);
		}
		if (ft_strcmp(lines[i], dlim) == 0)
			return (0);
		i++;
	}
	return (0);
}
