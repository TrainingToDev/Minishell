/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:42:24 by herandri          #+#    #+#             */
/*   Updated: 2025/01/26 00:24:37 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_format(const char *str, unsigned long *value, int *sign)
{
	*sign = 1;
	*value = 0;
	if (!str || *str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	if (!*str)
		return (0);
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		if (*value > (LONG_MAX / 10) || (*value == (LONG_MAX / 10)
				&& (*str - '0') > (LONG_MAX % 10)))
			return (0);
		*value = *value * 10 + (*str - '0');
		str++;
	}
	return (1);
}

static int	is_valid_integer(const char *str, long *result)
{
	unsigned long	value;
	int				sign;

	if (!is_valid_format(str, &value, &sign))
		return (0);
	*result = sign * (long)value;
	if (*result > LONG_MAX || *result < LONG_MIN)
		return (0);
	return (1);
}

void	cleanup_shell(t_minishell *shell)
{
    if (shell->fd_input != -1)
    {
        if (close(shell->fd_input) == -1)
            perror("Error close fd_input");
        shell->fd_input = -1;
    }
    if (shell->fd_output != -1)
    {
        if (close(shell->fd_output) == -1)
            perror("Error close fd_output");
        shell->fd_output = -1;
    }
	free_env_list(shell->env_list);
	free_token_list(shell->tokens);
	rl_clear_history();
}

int	ft_exit(t_minishell *shell, char **args)
{
	long	exit_status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!args[1])
		exit(status_manager(SUCCESS, STATUS_READ));
	if (!is_valid_integer(args[1], &exit_status))
	{
		print_error(E_EXIT, args[1], ERR_SYN);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		cleanup_shell(shell);
		exit(ERR_SYN);
	}
	if (args[2])
	{
		print_error(E_EXIT, "too many arguments\n", ERR_G);
		return (ERR_G);
	}
	exit_status = exit_status % 256;
	if (exit_status < 0)
		exit_status += 256;
	status_manager(exit_status, STATUS_WRITE);
	cleanup_shell(shell);
	exit((unsigned char)exit_status);
}
