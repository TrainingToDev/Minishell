/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:49:54 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 12:07:36 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char *input;
	int state; // atao eo @ env iny ilay ?
	t_parse *data;
	t_env *env_list;

	(void)argv;
	if (argc == 1)
	{
		env_list = get_env(env);
		while (1)
		{
			input = readline((const char*)getcwd(NULL, 0));
			data = get_struct(input);
			if (echo_command(data) == 1)
				state = 1;
			else if (echo_without_option(data) == 1)
				state = 1;
			else if (pwd_command(data) == 1)
				state = 1;
			else if (env_command(env_list, data) == 1)
				state = 1;
			else if (export_command(env_list, data) == 1)
				state = 1;
		}
		free(input);
	}
}