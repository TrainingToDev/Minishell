/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 01:50:28 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:42:18 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//test for args implementation

int	check_args(int argc, char **argv, char **envp)
{
	if (!envp || !*envp)
		ft_putendl_fd("minishell: Executed without env", 2);
	if (argc > 1)
    {
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("Invalide input", 2);
		exit(1);
    }
	return (0);
}
