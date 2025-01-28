/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plou.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 01:56:35 by herandri          #+#    #+#             */
/*   Updated: 2025/01/23 23:37:10 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_error_msg(int err_type)
{
	if (err_type == E_QUOTE)
		return ("minishell: syntax Unclosed quote\n");
	else if (err_type == E_SYNTAX)
		return ("minishell: syntax error near unexpected token `");
	else if (err_type == E_NODIR)
		return ("minishell: No such file or directory: ");
	else if (err_type == E_ISDIR)
		return ("minishell: Is a directory: ");
	else if (err_type == E_NOTDIR)
		return ("minishell: Not a directory: ");
	else if (err_type == E_PDENIED)
		return ("minishell: Permission denied: ");
	else if (err_type == E_NOCMD)
		return ("minishell: Command not found: ");
	else if (err_type == E_DUPFD)
		return ("minishell: dup2 failed\n");
	else if (err_type == E_FORK)
		return ("minishell: fork failed\n");
	else if (err_type == E_PIPE)
		return ("minishell: pipe failed\n");
	else if (err_type == E_NOMEM)
		return ("minishell: Cannot allocate memory\n");
	return (NULL);
}

void	*print_error(int err_type, char *param, int err)
{
	char	*error_message;

	status_manager(err, STATUS_WRITE);
	error_message = get_error_msg(err_type);
	if (!error_message)
	{
		ft_putstr_fd("minishell: error Unknown\n", 2);
		return (NULL);
	}
	ft_putstr_fd(error_message, 2);
	if (err_type == E_SYNTAX && param)
	{
		ft_putstr_fd(param, 2);
		ft_putstr_fd("'\n", 2); 
		return (NULL);
	}
	if (param)
		ft_putendl_fd(param, 2);
	return (NULL);
}

