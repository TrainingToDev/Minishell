/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:49:54 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/07 11:52:23 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	without_pipe(t_env *var, t_env *env, t_parse *data, char *input)
{

}


int	main(int argc, char **argv, char **env)
{
	char *input;
	int state; // atao eo @ env iny ilay ?
	t_parse *data;
	t_env *env_list;
	t_env *var;

	(void)argv;
	if (argc == 1)
	{
		env_list = get_env(env);
		var = local_variable();
		while (1)
		{
			input = readline((const char*)getcwd(NULL, 0));
			if (check_pipe(input) == 0)
			data = get_struct(input);
			if (add_new_var(data, var) == 1)
				state = 1;
			else if (echo_command(data) == 1)
			{
				state = 1;
				printf("%i\n", state);
			}
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