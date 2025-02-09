/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:05:42 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/31 11:25:10 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;

static void	init_minishell(t_minishell *shell, t_env_var *env_list)
{
	shell->env_list = env_list;
	shell->last_exit_status = 0;
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->nb_line_heredoc = 0;
	shell->running = 1;
	shell->fd_input = dup(STDIN_FILENO);
	status_manager(SUCCESS, STATUS_INIT);
	if (shell->fd_input == -1)
	{
		perror("dup STDIN");
		exit(1);
	}
	shell->fd_output = dup(STDOUT_FILENO);
	if (shell->fd_output == -1)
	{
		perror("duo STDOUT");
		exit(1);
	}
}

static char	*get_input(void)
{
	char	*prompt;
	char	*input;

	prompt = format_prompt();
	if (!prompt)
	{
		ft_putstr_fd("minishell: Error creating prompt\n", 2);
		return (NULL);
	}
	input = prompt_input(prompt);
	free(prompt);
	return (input);
}

static t_ast	*process_input(char *input, t_minishell *shell)
{
	t_token	*token_list;
	t_ast	*ast_root;

	token_list = lexer(input);
	if (!token_list)
		return (NULL);
	fast_export(token_list, shell);
	fast_unset(token_list, shell);
	mark_heredoc_delimiters(token_list);
	expand_token_list(token_list, shell);
	ast_root = parse(token_list, input);
	free_token_list(token_list);
	if (!ast_root)
		return (NULL);
	return (ast_root);
}

static void	execute_parsed_ast(t_ast *ast_root, t_minishell *shell)
{
	if (!ast_root)
		return ;
	execute_ast(ast_root, shell);
	free_ast(ast_root);
}

static void	minishell_loop(t_env_var *env_list)
{
	char		*input;
	t_ast		*ast_root;
	t_minishell	shell;

	init_minishell(&shell, env_list);
	while (shell.running)
	{
		input = get_input();
		if (!input)
		{
			if (g_status == SIGINT)
				exit(128 + SIGINT);
			else
				exit(0);
		}
		ast_root = process_input(input, &shell);
		free(input);
		if (!ast_root)
			continue ;
		execute_parsed_ast(ast_root, &shell);
	}
	cleanup_shell(&shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_var	*env_list;

	g_status = 0;
	env_list = NULL;
	check_args(argc, argv);
	env_list = convert_envp_to_list(envp);
	if (!env_list)
	{
		perror("Failed to initialize environment");
		return (1);
	}
	setup_signals();
	minishell_loop(env_list);
	rl_clear_history();
	return (0);
}
