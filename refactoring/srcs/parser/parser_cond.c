#include "minishell.h"

static t_ast *create_logic_node(t_token_type operator, t_ast *left, t_ast *right)
{
    t_ast *logic_node;

    logic_node = malloc(sizeof(t_ast));
    if (!logic_node)
        return (NULL);
    if (operator == TOKEN_AND)
        logic_node->type = NODE_AND;
    else
        logic_node->type = NODE_OR;
    logic_node->left = left;
    logic_node->right = right;
    return (logic_node);
}

t_ast *parse_conditional(t_parser *parser, t_ast *left, char *input)
{
    t_token_type	operator;
    t_ast			*right;

    if (is_token(parser, TOKEN_AND) 
		|| is_token(parser, TOKEN_OR))
    {
        operator = parser_advance(parser)->type;
        right = parse_pipe(parser, input);
        if (!right)
        {
            perror("conditional error");
            return (NULL);
        }
        return (create_logic_node(operator, left, right));
    }
    return (NULL);
}
