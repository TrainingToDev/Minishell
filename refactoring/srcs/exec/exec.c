/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:10:52 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 09:26:54 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static int execute_command(t_command *command, t_minishell *shell)//execute cmd
{
    int result;

    result = check_cmd(command);
    if (result != 0 || (!command || !command->argv 
		|| command->argc == 0))
			return (result);
    if (is_builtin(command->argv[0]))
        return (execute_builtin_cmd(command, shell));
    return (execute_external_cmd(command, shell));
}

int	execute_ast(t_ast *ast, t_minishell *shell)//main principal of exec
{
	if (!ast)
		return (1);
	if (ast->type == NODE_COMMAND)
	{
    	shell->nb_line_heredoc++;
		return (execute_command(ast->command, shell));
	}	
	else if (ast->type == NODE_PIPE)
		return (execute_pipeline(ast, shell));
	else if (ast->type == NODE_AND || ast->type == NODE_OR)
		return (execute_conditional(ast, shell));
	else if (ast->type == NODE_SUBSHELL)
		return (execute_subshell(ast, shell));
	else
		ft_putstr_fd("Erreur : Type de nœud AST inconnu\n", 2);
	return (1);
}