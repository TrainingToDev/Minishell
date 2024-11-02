/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:42:24 by herandri          #+#    #+#             */
/*   Updated: 2024/11/02 11:43:29 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_cmd(char *input)
{
    if (ft_strcmp(input, "exit") == 0)
	{
		free(input);
	}
}
