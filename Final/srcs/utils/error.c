/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:02:59 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/29 02:03:55 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_error_msg(int err_type)
{
	if (err_type == E_QUOTE)
		return ("minishell: syntax error ");
	else if (err_type == E_SYNTAX)
		return ("minishell: syntax error near unexpected token `");
	else if (err_type == E_DIR)
		return ("minishell: ");
	else if (err_type == E_CMD)
		return ("minishell: ");
	else if (err_type == E_DUPFD)
		return ("minishell: dup2 failed\n");
	else if (err_type == E_FORK)
		return ("minishell: fork failed\n");
	else if (err_type == E_PIPE)
		return ("minishell: pipe failed\n");
	else if (err_type == E_NOMEM)
		return ("minishell: error :\n");
	else if (err_type == E_VAR)
		return ("minishell: export: `");
	else if (err_type == E_VAR_O)
		return ("minishell: export: `': not a valid identifier");
	else if (err_type == E_EXIT)
		return ("minishell: exit: ");
	else if (err_type == E_SUP)
		return ("minishell: ");
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
		ft_putstr_fd(param, 2);
	return (NULL);
}
