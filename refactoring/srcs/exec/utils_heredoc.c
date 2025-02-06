/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:39:22 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/31 11:39:35 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_params(t_hdc *cnt, char *dlim, t_minishell *shell)
{
	if (!cnt || !dlim || !shell)
	{
		perror("Invalid parameters heredoc.\n");
		return (0);
	}
	return (1);
}

char	*read_user_input(char *dlim, t_minishell *shell)
{
	char	*line;

	line = readline("\001"COLOR_BLUE"\002""heredoc> ""\001"COLOR_RESET"\002");
	if (!line)
	{
		printf(MSG_1 "%d" MSG_2 "%s" MSG_3, shell->nb_line_heredoc , dlim);
		return (NULL);
	}
	return (line);
}

int	insert_line(t_hdc *cnt, char *line)
{
	char	**new_lines;
	size_t	i;

	new_lines = malloc(sizeof(char *) * (cnt->count + 1));
	if (!new_lines)
	{
		perror("malloc");
		free(line);
		return (0);
	}
	i = 0;
	while (i < cnt->count)
	{
		new_lines[i] = cnt->lines[i];
		i++;
	}
	new_lines[cnt->count] = line;
	free(cnt->lines);
	cnt->lines = new_lines;
	cnt->count++;
	return (1);
}

char	*trim_quotes(char *str)
{
	if (!str || (str[0] != '\'' && str[0] != '\"'))
		return (ft_strdup(str));
	return (ft_strtrim(str, "\"'"));
}

t_hdc	*get_heredoc_lines(char *input, char *dlim)
{
	t_hdc	*cnt;
	char	**lines;

	if (!input || !dlim)
		return (NULL);
	cnt = init_heredoc();
	if (!cnt)
		return (NULL);
	lines = split_lines(input);
	if (!lines)
	{
		free(cnt);
		return (NULL);
	}
	if (get_lines(cnt, lines, dlim) == -1)
	{
		free_heredoc_content(cnt);
		free_split(lines);
		free(cnt);
		return (NULL);
	}
	free_split(lines);
	return (cnt);
}
