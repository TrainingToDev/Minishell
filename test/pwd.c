/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:04:20 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 11:34:22 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_command(t_parse *data)
{
	if (exact_command(data->command, "pwd") != 1)
		return (0);
	if (data->option != NULL)
		return (-1); // error
	else
	{
		printf("%s\n", getcwd(NULL, 0));
		free_struct(data);
		return (1);
	}
}