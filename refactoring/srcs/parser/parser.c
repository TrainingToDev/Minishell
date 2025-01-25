#include "minishell.h"

t_ast	*parse(t_token *tokens, char *input)
{
    t_parser	parser;
	t_ast		*root;

	parser.current = tokens;
	root = parse_list(&parser, input);
	if (root && parser.current != NULL)
    {
        perror("Unexpected token at end of input");
        free_ast(root);
        root = NULL;
    }
    return (root);
}
