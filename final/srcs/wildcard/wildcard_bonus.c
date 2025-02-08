/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:24:57 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/05 04:52:18 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_match(const char *target, const char *str)
{
	if (*target == '\0')
		return (*str == '\0');
	if (*target == '*')
	{
		while (*(target + 1) == '*')
			target++;
		while(*str != '\0')
		{
			if (check_match(target + 1, str))
				return (true);
			str++;
		}
		return (check_match(target + 1, str));
	}
	else if (*target == *str)
		return (check_match(target + 1, str + 1));
	else
		return (false);
}

static void match_tokens(t_wildcard *data, t_token *token)
{
	t_token *new_token;

	while ((data->entry = readdir(data->dir)) != NULL)
	{
		if (data->entry->d_name[0] == '.' && token->value[0] != '.')
			continue ;
		if (check_match(token->value, data->entry->d_name))
		{
			new_token = create_token(token->type, data->entry->d_name, 0);
			if (!new_token)
				continue ;
			if (!data->expanded)
				data->expanded = new_token;
			else
				data->last->next = new_token;
			data->last = new_token;
			data->count++;
		}
	}
}

static t_token *check_wildcard(t_token *cur, t_token **tokens, t_token *prev)
{
    t_token	*expanded;

    expanded = expand_wildcard(cur);
    if (prev)
        prev->next = expanded;
    else
        *tokens = expanded;

    while (expanded && expanded->next)
        expanded = expanded->next;

    if (expanded)
        return expanded->next;
    return NULL;
}

t_token *expand_wildcard(t_token *token)
{
	t_wildcard	data;

	data.expanded = NULL;
	data.last = NULL;
	data.count = 0;
	data.dir = opendir(".");
	if (!data.dir)
	{
		perror("opendir");
		return (token);
	}
	match_tokens(&data, token);
	closedir(data.dir);

	if (data.count == 0)
		return (token);
	free(token->value);
	free(token);
	return (data.expanded);
}

void expand_list(t_token **tokens, t_minishell *shell)
{
    t_token	*cur;
    t_token	*prev;

    cur = *tokens;
    prev = NULL;
    (void)shell;

    while (cur)
    {
        if (cur->expand && ft_strchr(cur->value, '*'))
            cur = check_wildcard(cur, tokens, prev);
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}
