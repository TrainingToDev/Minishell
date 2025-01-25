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

#include "../minishell.h"

static char *process_dollar(const char *src, size_t *i, char *result, t_minishell *shell)
{
    if (src[*i + 1] == '?')
    {
		result = append_exit_status(result, shell);
		if (!result)
			return (NULL);
		*i += 2; // Sauter '$?'
	}
	else
	{
		result = append_var_value(src, i, result, shell);
		if (!result)
			return (NULL);
	}
	return (result);
}
static char	*process_normal_char(const char *src, size_t *i, char *result)
{
	result = append_char_to_result(result, src[*i]);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}

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

void	main_heredoc(void)
{
	setup_signal(SIGINT, SIG_IGN);
	setup_signal(SIGQUIT, SIG_IGN);
}