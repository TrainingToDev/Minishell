/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:39:06 by herandri          #+#    #+#             */
/*   Updated: 2024/11/17 13:33:47 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_simple_command(t_token **tokens)
{
	t_command	*cmd;
	t_ast		*ast;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->redirs = NULL;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		add_argument(cmd, (*tokens)->value);
		*tokens = (*tokens)->next;
	}
	while (*tokens && is_redirection_token((*tokens)->type))
	{
		if (!add_redirection(cmd, tokens))
		{
			free_command(cmd);
			return (NULL);
		}
	}
	if (cmd->argc == 0 && cmd->redirs == NULL)
	{
		free_command(cmd);
		return (NULL);
	}
	ast = malloc(sizeof(t_ast));
	if (!ast)
	{
		free_command(cmd);
		return (NULL);
	}
	ast->type = NODE_COMMAND;
	ast->command = cmd;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

// main for test

int main (void)
{
	


	
}
































t_ast	*init_parse(t_token **in)
{
	
}







int	main(void)
{
	
	return(0);
}