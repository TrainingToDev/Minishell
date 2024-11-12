/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:26:55 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 11:52:19 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need refactoring

void add_to_history(const char *input)
{
	if (input && *input)
		add_history(input);
}

int init_minishell(t_minishell *shell, char **envp)
{
	shell->env_list = convert_envp_to_list(envp);
	if (!shell->env_list)
	{
		ft_putendl_fd("Error initializing envp", STDERR_FILENO);
		return (-1);
	}
	shell->last_exit_status = 0;
	shell->interactive = isatty(STDIN_FILENO);
	setup_signals(shell);
	return (0);
}

int minishell_loop(t_minishell *shell)
{
	char    *input;
	t_ast   *ast;

	while (1)
	{
		input = readline(get_prompt(shell));
		if (!input)
			break;
		if (*input)
			add_to_history(input);
		ast = parse_input(input);
		free(input);
		if (!ast)
			continue;
		execute_ast(shell, ast);
		free_ast(ast);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (shell->last_exit_status);
}

int is_operator(const char *str)
{
    if (ft_strncmp(str, "&&", 2) == 0 || ft_strncmp(str, "||", 2) == 0 ||
        ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
        return (2);
    else if (*str == '|' || *str == '>' || *str == '<' ||
             *str == '(' || *str == ')')
        return (1);
    else
        return (0);
}

int is_quote(char c)
{
    return (c == '\'' || c == '\"');
}
