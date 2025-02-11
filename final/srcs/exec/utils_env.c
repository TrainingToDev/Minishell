/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:44:24 by miaandri          #+#    #+#             */
/*   Updated: 2025/02/01 23:43:47 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(t_env_var *env)
{
	t_env_var	*cur;
	int			count;

	count = 0;
	cur = env;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

char	**convert_env_list(t_env_var *env_list)
{
	t_env_var	*cur;
	char		**env_array;
	char		*entry;
	int			i;

	env_array = malloc(sizeof(char *) * (count(env_list) + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	cur = env_list;
	while (cur)
	{
		entry = join_free(ft_strjoin(cur->key, "="), cur->value, 1);
		if (!entry)
		{
			free_str_array(env_array);
			return (NULL);
		}
		env_array[i++] = entry;
		cur = cur->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	find_cmd_path(t_command *cmd, t_minishell *shell, char **path)
{
	struct stat	path_stat;

	if (stat(cmd->argv[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		print_error(E_CMD, cmd->argv[0], ERR_CMD);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (1);
	}
	*path = find_command_path(cmd->argv[0], shell->env_list);
	if (!(*path))
	{
		print_error(E_CMD, cmd->argv[0], ERR_CMD);
		ft_putendl_fd(": command not Found", STDERR_FILENO);
		return (1);
	}
	return (0);
}
