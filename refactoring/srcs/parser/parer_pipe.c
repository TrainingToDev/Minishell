#include "minishell.h"

t_ast	*create_pipe_node(t_ast *cmd, t_ast *next_pipeline)
{
	t_ast	*pipe_node;

	pipe_node = malloc(sizeof(t_ast));
	if (!pipe_node)
	{
		free_ast(cmd);
		free_ast(next_pipeline);
		return (NULL);
	}
	pipe_node->type = NODE_PIPE;
	pipe_node->left = cmd;
	pipe_node->right = next_pipeline;
	pipe_node->command = NULL;
	return (pipe_node);
}

t_ast	*parse_pipe(t_parser *parser, char *input)
{
	t_ast	*cmd;
	t_ast	*next_pipeline;
	t_ast	*pipe_node;

	cmd = parse_cmd(parser, input);
	if (!cmd)
		return (NULL);
	if (is_token(parser, TOKEN_PIPE))
	{
		parser_advance(parser);
		next_pipeline = parse_pipe(parser, input);
		if (!next_pipeline)
		{
			print_error(E_PIPE, parser->current->value, 9);
			free_ast(cmd);
			return (NULL);
		}
		pipe_node = create_pipe_node(cmd, next_pipeline);
		return (pipe_node);
	}
	return (cmd);
}