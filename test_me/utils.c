/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:35:45 by herandri          #+#    #+#             */
/*   Updated: 2024/11/02 12:02:59 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(char *cmd, char **envp)
{
	t_data_path	vars;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!(*envp))
		return (NULL);
	vars.paths = ft_split(*envp + 5, ':');
	vars.i = 0;
	while (vars.paths[vars.i])
	{
		vars.path = ft_strjoin(vars.paths[vars.i], "/");
		vars.full_path = ft_strjoin(vars.path, cmd);
		free(vars.path);
		if (access(vars.full_path, X_OK) == 0)
		{
			free_split(vars.paths);
			return (vars.full_path);
		}
		free(vars.full_path);
		vars.i++;
	}
	free_split(vars.paths);
	return (NULL);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_error(const char *message, int exit_code)
{
	perror(message);
	exit(exit_code);
}

void	print_error_message(char *shell, int errnum, char *filename)
{
	write(STDERR_FILENO, shell, ft_strlen(shell));
	write(STDERR_FILENO, ": ", 2);
	if (errnum == CMD_NOT_FOUND)
		write(STDERR_FILENO, "command not found", 18);
	else
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, filename, ft_strlen(filename));
	write(STDERR_FILENO, "\n", 1);
}

void ft_realloc(void *ptr, size_t size)
{
	
}