/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:03:35 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/05 04:54:37 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_exit_status(char *res, t_minishell *shell)
{
	char	*exit_status;
	char	*temp;

	exit_status = ft_itoa(shell->last_exit_status);
	if (!exit_status)
	{
		free(res);
		return (NULL);
	}
	temp = ft_strjoin(res, exit_status);
	free(exit_status);
	free(res);
	return (temp);
}

static char	*append_char_to_result(char *res, char c)
{
	char	*temp;

	temp = ft_strjoin_char(res, c);
	free(res);
	return (temp);
}

static char	*process_normal_char(char *src, size_t *i, char *res)
{
	res = append_char_to_result(res, src[*i]);
	if (!res)
		return (NULL);
	(*i)++;
	return (res);
}

static char	*proc_dlr(char *src, size_t *i, char *res, t_minishell *shell)
{
	if (src[*i + 1] == '?')
	{
		res = append_exit_status(res, shell);
		if (!res)
			return (NULL);
		*i += 2;
	}
	else
	{
		res = add_vval(src, i, res, shell);
		if (!res)
			return (NULL);
	}
	return (res);
}

char	*expand_variables_in_str(char *src, t_minishell *shell)
{
	size_t	i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
		{
			res = proc_dlr(src, &i, res, shell);
			if (!res)
				return (NULL);
		}
		else
		{
			res = process_normal_char(src, &i, res);
			if (!res)
				return (NULL);
		}
	}
	return (res);
}
