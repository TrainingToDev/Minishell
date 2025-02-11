/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:38:58 by herandri          #+#    #+#             */
/*   Updated: 2025/02/05 04:56:53 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_env(t_env_var **env_array, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_array[i]->key, STDOUT_FILENO);
		if (env_array[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_array[i]->value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	export_error(char *arg)
{
	print_error(E_VAR, arg, ERR_G);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (1);
}

void	display_exported(t_minishell *shell)
{
	int			count;
	t_env_var	**env_array;

	count = count_vars(shell->env_list);
	if (count == 0)
		return ;
	env_array = create_array(shell->env_list, count);
	if (!env_array)
		return ;
	sort_array(env_array, count);
	display_env(env_array, count);
	free(env_array);
}
