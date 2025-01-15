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

//| hola : should give error
//cat < gdfgdgdf < main.c << end mande aloa ilay heredoc zay vao mande ilay erreur @ fichier voalohany
//<<"gg" ->expand <<gg ->don't expand

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
    return (0);
}
int g_sign = 0;

int main (int argc, char **argv, char **en)
{
	t_env *env;
	t_export *exp;
	t_list *list;
	char	*prompt;
	char	*input;
	t_token **token;
	int	len;
    
	(void)argv;
	(void)en;
	if (argc != 1)
		//perror ("invalid argument");
		return (write(2, "wrong parameter\n", 15));
	env = get_env(en);
	exp = get_export_list(en);
	list = get_all_builtins();
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
		//prompt = ft_strjoin(getcwd(NULL, 0), " ");//miteraka error
		prompt = "MINISHELL>";
		input = readline((const char *)prompt);
		add_history(input);
		len = check_pipe(input);
		if (input[0] != '\0')
		{
			if (input_checking(input) == -1)
				;		
			else
			{
				input = change(input);
				printf ("change : %s\n", input);  
				//test = split_expand(input);
				input = new_expand(input, env);
				printf ("after expand : %s\n", input);
				token = get_all_token(get_pile(input), len);
				token = get_all_state(token);
				pipe_implemantations(token, len, list, env, exp);
				free (token);
				//pipe_implementation(token, count_pipe(token));
			}
		}
		else
		{
			free (input);
		}
		//data = get_struct(input);//test fini
		//data = get_data(input, check_pipe(input));
		//printf ("%i\n", get_number_of(input, '>'));
	}
}


/*
cat << t
rl_unix_word_rubout
raise
rl_directory_completion_hook
t
*/