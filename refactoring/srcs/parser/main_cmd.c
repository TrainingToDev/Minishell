#include "minishell.h"

t_ast	*create_cmd_node(void)
{
	t_ast	*cmd;

	cmd = malloc(sizeof(t_ast));
	if (!cmd)
		return (NULL);

	cmd->type = NODE_COMMAND;
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->command = NULL;

	return (cmd);
}

t_ast	*parse_cmd(t_parser *parser, char *input)
{
	t_ast	*cmd;

	if (is_token(parser, TOKEN_LPAREN))
		return (parse_subshell(parser, input));
	cmd = create_cmd_node();
	if (!cmd)
		return (NULL);
	cmd->command = parse_simple_cmd(parser, input);
	if (!cmd->command)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
