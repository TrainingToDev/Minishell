#include "minishell.h"

char    *prompt_input(char *prompt)
{
	char    *input;

	input = NULL;
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	if (!input)
	{
		write(1, "exit\n", 5);
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}

int run_shell(void)
{
	char	*input;
	char	*prompt;
	t_token	*tokens;

	while(1)
	{
		prompt = format_prompt();
		if (!prompt || !*prompt)
		{
			ft_putstr_fd("Error: Unable to format prompt.\n", 2);
			return (1);
		}
		input = prompt_input(prompt);
		free(prompt);
		if (!input)
		{
			printf("CTRL+D\n");
			break ;
		}
		if (*input)
		{
			tokens = lexer(input);
			if (!tokens)
			{
				printf("not token\n");
				status_manager(258, STATUS_WRITE);
				free(input);
				continue ;
			}
			// tokens->value = compare(tokens->value, env);
			print_tokens(tokens);
			free_token_list(tokens);
			tokens = NULL;
		}
		free(input);
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	check_args(argc, argv);
	setup_signals();
	run_shell();

	return (EXIT_SUCCESS);
}


// check
echo <> p