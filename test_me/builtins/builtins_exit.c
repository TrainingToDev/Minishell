/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:42:24 by herandri          #+#    #+#             */
/*   Updated: 2024/11/17 11:38:57 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// first implemetation exit

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	cleanup_shell(t_minishell *shell)
{
	// free list envp
	free_env_list(shell->env_list);
	
	// free other ressource
	// ...
}

int	builtin_exit(t_minishell *shell, char **args)
{
	int	exit_status;

	ft_putendl_fd("exit", STDERR_FILENO);
	
	if (!args[1])
	{
		// not argument : use status for prec cmd
		exit(shell->last_exit_status);
	}
	// not numeric Argument
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	// many arguments
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		shell->last_exit_status = 1;
		return (1);
	}
	exit_status = ft_atoi(args[1]) % 256;
	if (exit_status < 0)
		exit_status += 256;
	cleanup_shell(shell);
	exit(exit_status);
}
// be comming for test

//mini-test empty
/* void exit_cmd(char *input)
{
	
} */
