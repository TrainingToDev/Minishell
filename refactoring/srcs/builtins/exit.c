/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:58:30 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 12:49:00 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_valid_integer(const char *str, long *result)
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

static void	cleanup_shell(t_minishell *shell)
{
	// free liste var env
	free_env_list(shell->env_list);
	rl_clear_history();
	// ..
}

int ft_exit(t_minishell *shell, char **args)
{
    long	exit_status;

    ft_putendl_fd("exit", STDOUT_FILENO);
    if (!args[1])
        exit(shell->last_exit_status);
    if (!is_valid_integer(args[1], &exit_status))
    {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putendl_fd(": numeric argument required", STDERR_FILENO);
        cleanup_shell(shell);
        exit(255);
    }
    if (args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
        shell->last_exit_status = 1;
        return (1);
    }
    exit_status = exit_status % 256;
    if (exit_status < 0)
        exit_status += 256;
    cleanup_shell(shell);
    exit((unsigned char)exit_status);
}