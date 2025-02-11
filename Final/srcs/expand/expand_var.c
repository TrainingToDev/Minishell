/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:03:35 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/29 06:38:41 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_vlen(char *src, size_t *i)
{
	size_t	start;

	(*i)++;
	start = *i;
	while (src[*i] && (ft_isalnum(src[*i]) || src[*i] == '_'))
		(*i)++;
	return (*i - start);
}

static char	*join_var(t_varinfo var, char *res, t_minishell *shell)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	var_name = ft_substr(var.src, var.start, var.len);
	if (!var_name)
	{
		free(res);
		return (NULL);
	}
	var_value = compare(var_name, shell->env_list);
	free(var_name);
	if (!var_value)
		var_value = ft_strdup("");
	tmp = ft_strjoin(res, var_value);
	free(var_value);
	free(res);
	return (tmp);
}

static char	*handle_empty(char *res)
{
	char	*tmp;

	tmp = concat_char(res, '$');
	free(res);
	return (tmp);
}

char	*add_vval(char *src, size_t *i, char *res, t_minishell *shell)
{
	t_varinfo	var;
	size_t		len;

	var.src = NULL;
	var.start = 0;
	var.len = 0;
	len = get_vlen(src, i);
	var.src = src;
	var.start = (*i) - len;
	var.len = len;
	if (len > 0)
		return (join_var(var, res, shell));
	else
		return (handle_empty(res));
}
