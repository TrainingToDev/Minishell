/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:11:50 by herandri          #+#    #+#             */
/*   Updated: 2024/11/14 11:35:23 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prompt resolved

char	*get_prompt(t_minishell *shell)
{
	char	*cwd;
	char	*prompt;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_strdup("minishell");
		if (!cwd)
			return (NULL);
	}
	prompt = ft_strjoin("\001"COLOR_GREEN"\002", cwd);
	free(cwd);
	if (!prompt)
		return (NULL);
	tmp = prompt;
	prompt = ft_strjoin(prompt, "\001"COLOR_RESET"002" " $ ");
	if (!prompt)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (prompt);
}

char *get_env_value(t_env_var *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
