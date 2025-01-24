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
//the prev prompt caused leaks

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

static t_shell *get_shell(char **en)
{
	t_shell *shell;

	shell = (t_shell*)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = get_env(en);
	shell->exp = get_export_list(en);
	shell->built = get_all_builtins();
	return (shell);
}

int main (int argc, char **argv, char **en)
{
	t_shell *shell;
	t_token **token;
	char	*input;
	int	len;
    
	(void)argv;
	if (argc != 1)
		return (write(2, "wrong parameter\n", 15));
	shell = get_shell(en);
	while (1)
	{
		input = readline((const char *)"MINISHELL>");
		add_history(input);
		len = check_pipe(input);
		if (input[0] != '\0' || chech_space(input) != 1)
		{
			if (input_checking(input) == -1)
				;		
			else
			{
				input = change(input);
				printf ("change : %s\n", input);
				input = new_expand(input, shell);//place of expand a discuter
				printf ("after expand : %s\n", input);
				token = get_all_token(get_pile(input), len);
				token = get_all_state(token);
				pipe_implemantations(token, len, shell);
			}
		}
	}
}


/*
cat << t
rl_unix_word_rubout
raise
rl_directory_completion_hook
t
*/