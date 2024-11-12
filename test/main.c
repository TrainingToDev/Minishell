/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:49:54 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/12 15:32:26 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
			//if (check_pipe(input) == 0)
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
*/
/*
static void	proc_routine(t_env *env, t_env *var, t_parse *data)
{
	
} 
*/



int main (int argc, char **argv, char **en)
{
	//t_env *var;
	//t_env *env;
	t_parse *data;//tableau de data ity len isan'ny proc
	char	*prompt;
	char	*input;
	int i;
	
	(void)argv;
	(void)en;
	if (argc != 1)
		perror ("invalid argument\n");
		//return (write(2, "wrong parameter\n", 15));
	//var = local_variable();
	//env = get_env(en);
	while (1)
	{
		prompt = ft_strjoin(getcwd(NULL, 0), " ");
		input = readline((const char *)prompt);
		printf("%i\n", check_pipe(input));
		data = get_struct(input);
		//data = get_data(input, check_pipe(input));
		i = 0;
		while (i < get_number_of(input, '>'))
		{
			printf (">%s\n", data->input[i]);
			i++;
		}
		
		free(prompt);
		free (input);
	}
}
