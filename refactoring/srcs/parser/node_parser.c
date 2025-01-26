#include "minishell.h"

t_ast	*create_ast_node(t_node_type type)
{
    t_ast	*node;

	node = malloc(sizeof(t_ast));
    if (!node)
    {
        perror("Error allocating memory for AST node");
        return (NULL);
    }
    node->type = type;
    node->command = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

t_command *create_cmd(void)
{
    t_command	*cmd;

	cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->argc = 0;
    cmd->redirs = NULL;
    return (cmd);
}

t_redir *create_redir(void)
{
    t_redir	*redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = REDIR_INVALID;
    redir->filename = NULL;
    redir->content = NULL;
    redir->next = NULL;
    return (redir);
}
