/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:08:37 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 16:42:18 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_variables_in_str(const char *src, t_minishell *shell)
{
    size_t	i;
    char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
		{
			result = process_dollar(src, &i, result, shell);
			if (!result)
				return (NULL);
		}
		else
		{
			result = process_normal_char(src, &i, result);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}

char *process_input_line(char *line, const char *delim, t_minishell *shell)
{
    char	*expanded_line;

	expanded_line = NULL;
    if (ft_strcmp(line, delim) == 0)
	{
        free(line);
        return (NULL);
    }
    expanded_line = expand_variables_in_str(line, shell);
    free(line);
    if (!expanded_line)
	{
        perror("expand_variables_in_str");
    }
    return (expanded_line);
}
