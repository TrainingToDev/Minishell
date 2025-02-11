/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:04:20 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/26 00:23:40 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_minishell *shell, char **args)
{
	char	*cwd;

	(void) shell;
	if (args[1] && args[1][0] == '-')
	{
		print_error(E_SUP, "pwd: ", ERR_SYN);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": option not accepted", STDERR_FILENO);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		status_manager(SUCCESS, STATUS_WRITE);
		return (0);
	}
	else
	{
		perror("pwd: getcwd()");
		return (1);
	}
}
