/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:24:45 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 11:18:56 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_struct(t_parse *data)
{
    free(data->command);
    free(data->option);
    free(data->param);
    free (data);
}

int	exact_command(char *data, char *command)
{
	int	i;

	i = 0;
	if (ft_strlen(data) != ft_strlen(command))
	{
		// printf("%i->%i\n", (int)ft_strlen(data) , (int)ft_strlen(command));
		return (0);
	}
	while (data[i])
	{
		if (data[i] != command[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_alpha(int c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97))
		return (1);
	return (0);
}

int is_quote(char *string)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (string[i])
	{
		if (string[i] == '"' || string[i] == '\'')
			check += 1;
		i++;
	}
	if ((check % 2) == 0)
		return (1);
	else
		return (0);
}
