/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:31:54 by herandri          #+#    #+#             */
/*   Updated: 2024/11/17 11:42:49 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"



int add_argument(t_command *cmd, const char *arg)
{
	char **new_argv;
	char *new_arg;
	int i;

	new_argv = malloc(sizeof(char *) * (cmd->argc + 2));
	i = 0;
	if (!new_argv)
		return (0);
	while (i < cmd->argc)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_arg = ft_strdup(arg);
	if (!new_arg)
	{
		free(new_argv);
		return (0);
	}
	new_argv[cmd->argc] = new_arg;
	new_argv[cmd->argc + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	cmd->argc += 1;
	return (1);
}

int parse_all_arguments(t_token **tokens, t_command *cmd)
{
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		if (!add_argument(cmd, (*tokens)->value))
			return (0);
		*tokens = (*tokens)->next;
	}
	return (1);
}

int parse_all_redirections(t_token **tokens, t_command *cmd)
{
	while (*tokens && is_redirection_token((*tokens)->type))
	{
		if (!parse_redirections(tokens, cmd))
			return (0);
	}
	return (1);
}

t_ast *parse_simple_command(t_token **tokens)
{
	t_command *cmd;
	t_ast *ast;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	if (!parse_all_redirections(tokens, cmd)) // redir before arg
		return (free_command_with_error(cmd));
	if (!parse_all_arguments(tokens, cmd)) // add arg
		return (free_command_with_error(cmd));
	if (!parse_all_redirections(tokens, cmd)) // redir after arg
		return (free_command_with_error(cmd));
	if (!validate_command(cmd))
		return (free_command_with_error(cmd));
	ast = create_ast_node(NODE_COMMAND, cmd);
	if (!ast)
		return (free_command_with_error(cmd));
	while (*tokens && (*tokens)->type != TOKEN_PIPE) //manage arg(+)
    {
		if ((*tokens)->type == TOKEN_WORD && cmd->redirs && cmd->redirs->type == REDIR_HEREDOC)
        {
            *tokens = (*tokens)->next;
            continue; //>>
        }
        display_error((*tokens)->value);
        *tokens = (*tokens)->next;
    }
	return (ast);
}











t_ast execute_command()
{
    // need test
}

t_ast execute_pipeline()
{
    // need test
}

t_ast execute_logical()
{
    // need test
}
  
t_ast execute_subshell()
{
    // need test
}
