/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 07:31:15 by miaandri          #+#    #+#             */
/*   Updated: 2024/12/07 03:40:40 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int input_checking(char *input)
{
	if (pipe_void(input) == -1)
	{
		free(input);
		return (-1);
	}
	if (check_redir(input) == -1)
	{
		free (input);
		return (-1);
	}
	if (valid_pipe(input) != check_pipe(input))
    {
        free(input);
        write (2, "invalid pipe\n", 13);
        return (-1);
    }
	if (quote_number(input) != 0)
    {
		free(input);
        write (2, "unclosed quote\n", 15);
        return (-1);
    }
    else if (quote_number(input) == 0)
        return (1);
    return (0);
}
int g_sign = 0;

int main (int argc, char **argv, char **en)
{
	//t_env *var;
	//t_env *env;
	//t_list *list;
	//int nbr_pipe;
	//t_parse *data;//tableau de data ity len isan'ny proc
	char	*prompt;
	char	*input;
	t_token **token;
	int	len;
    
	(void)argv;
	(void)en;
	if (argc != 1)
		//perror ("invalid argument");
		return (write(2, "wrong parameter\n", 15));
	//var = local_variable();
	//env = get_env(en);
	//list = get_all_builtins();
	/*
	while (env)
	{
		printf("var : %s\n", env->var);
		printf("value : %s\n", env->value);
		env = env->next;
	}
	*/
	while (1)
	{
		prompt = ft_strjoin(getcwd(NULL, 0), " ");
		input = readline((const char *)prompt);
		add_history(input);
	//	nbr_pipe = check_pipe(input);
		if (input[0] != '\0')
		{
        	len = valid_pipe(input);
			if (input_checking(input) == -1)
				;
			else
			{
				input = change(input);
				split_expand(input);
				token = get_all_token(get_pile(input), len);
				token = get_all_state(token);
				//state_command(token, nbr_pipe, list);
				//pipe_implementation(token, count_pipe(token));
			}
			free (prompt);
		}
		else
		{
			free (input);
			free (prompt);
		}
		//data = get_struct(input);//test fini
		//data = get_data(input, check_pipe(input));
		//printf ("%i\n", get_number_of(input, '>'));
	}
}