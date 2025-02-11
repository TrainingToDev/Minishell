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

static char	*join_char(char *res, char c)
{
	char	*temp;

	if (!res)
		return (NULL);
	temp = concat_char(res, c);
	free(res);
	return (temp);
}

char	*expand_var(char *src, t_minishell *shell)
{
	t_state	s;
	char	*res;

	s.index = 0;
	s.single_quote = 0;
	s.double_quote = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (src[s.index])
	{
		res = scan_token(src, &s, res, shell);
		if (!res)
			return (NULL);
	}
	return (res);
}

char	*join_exit_status(char *res, t_minishell *shell)
{
	char	*exit_status;
	char	*temp;

	shell->last_exit_status = status_manager(SUCCESS, STATUS_READ);
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

char	*add_char(char *src, size_t *i, char *res)
{
	res = join_char(res, src[*i]);
	if (!res)
		return (NULL);
	(*i)++;
	return (res);
}

char	*proc_dlr(char *src, size_t *i, char *res, t_minishell *shell)
{
	if (!res || !src)
		return (NULL);
	if (src[*i + 1] == '?')
	{
		res = join_exit_status(res, shell);
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
