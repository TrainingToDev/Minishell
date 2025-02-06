/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:55:20 by herandri          #+#    #+#             */
/*   Updated: 2025/02/06 03:16:14 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_var(t_env_var *env_var)
{
	if (env_var)
	{
		free(env_var->key);
		free(env_var->value);
		free(env_var);
	}
}

void	free_env_list(t_env_var *env_list)
{
	t_env_var	*cur;
	t_env_var	*next;

	cur = env_list;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
}

void	fast_export(t_token *tokens, t_minishell *shell)
{
	t_token	*cur;
	t_token	*next;

	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD 
		&& ft_strcmp(cur->value, "export") == 0)
		{
			next = cur->next;
			while (next && next->type == TOKEN_WORD)
			{
				export_arg(shell, next->value);
				next = next->next;
			}
		}
		cur = cur->next;
	}
}

void fast_unset(t_token *tokens, t_minishell *shell)
{
	t_token	*cur;
	t_token	*arg;

	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD 
			&& ft_strcmp(cur->value, "unset") == 0)
		{
			arg = cur->next;
			while (arg && arg->type == TOKEN_WORD)
			{
				remove_env_var(shell, arg->value);
				arg = arg->next;
			}
		}
		cur = cur->next;
	}
}
