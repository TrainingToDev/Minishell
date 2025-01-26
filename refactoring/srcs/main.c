#include "minishell.h"

static void init_minishell(t_minishell *shell, t_env_var *env_list)
{
	shell->env_list = env_list;
	shell->last_exit_status = 0;
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->running = 1;
	shell->fd_input = STDIN_FILENO;
	shell->fd_output = STDOUT_FILENO;
	shell->nb_line_heredoc = 0;
}

static void minishell_loop(t_env_var *env_list)
{
	char		*prompt;
	char		*input;
	t_token		*token_list;
	t_ast		*ast_root;
	t_minishell	shell;


	prompt = NULL;
	input = NULL;
	token_list = NULL;
	ast_root = NULL;
	init_minishell(&shell, env_list);
	while (shell.running)
	{
		// 1) Format prompt
		prompt = format_prompt();
		if (!prompt)
		{
			ft_putstr_fd("minishell: Error creating prompt\n", 2);
			break;
		}

		// 2) Get user input
		input = prompt_input(prompt);
		free(prompt);

		// Handle ctrl+D (EOF)
		if (!input)
			break;

		// 3) Tokenize input
		token_list = lexer(input);
		if (!token_list)
		{
			free(input);
			continue;
		}
		printf("------>>>> TOKEN:\n");
		print_tokens(token_list);

		// 4) Parse tokens
		ast_root = parse(token_list, input);

		free_token_list(token_list);
		token_list = NULL;

		if (!ast_root)
		{
			free(input);
			continue;
		}
		printf("------>>>> Parser:\n");
		print_ast(ast_root, 0);

		// 5) Execute AST
		printf("\n------------execution---------\n");
		execute_ast(ast_root, &shell);

		// Free resources
		free_ast(ast_root);
		ast_root = NULL;
		free(input);
		input = NULL;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_env_var *env_list = NULL;

	check_args(argc, argv);
	env_list = convert_envp_to_list(envp);
	if (!env_list)
	{
		ft_putstr_fd("minishell: Failed to initialize environment\n", 2);
		return (1);
	}
	main_signals();
	minishell_loop(env_list);
	free_env_list(env_list);
	rl_clear_history();
	return (0);
}
