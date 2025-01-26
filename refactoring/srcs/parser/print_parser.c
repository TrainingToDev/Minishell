#include "minishell.h"

static void print_node_type(t_ast *ast)
{
    if (ast->type == NODE_COMMAND)
        printf("NODE_COMMAND: ");
    else if (ast->type == NODE_PIPE)
        printf("NODE_PIPE: ");
    else if (ast->type == NODE_AND)
        printf("NODE_AND: ");
    else if (ast->type == NODE_OR)
        printf("NODE_OR: ");
    else if (ast->type == NODE_SUBSHELL)
        printf("NODE_SUBSHELL: ");
    else
        printf("UNKNOWN NODE: ");
}

static void print_command_args(t_command *command)
{
    int i = 0;

    if (!command)
        return;
    printf("[ ");
    while (i < command->argc)
    {
        printf("%s ", command->argv[i]);
        i++;
    }
    printf("]\n");
}

static void heredoc_content(t_redir *redir, int depth)
{
    size_t j;

    if (redir->content)
    {
        j = 0;
        while (j < redir->content->count)
        {
            print_indentation(depth + 2);
            printf("Line %zu: %s\n", j + 2, redir->content->lines[j]);
            j++;
        }
    }
}

static void print_redirections(t_redir *redir, int depth)
{
    while (redir)
    {
        print_indentation(depth + 1);

        if (redir->type == REDIR_IN)
            printf("REDIR_IN: %s\n", redir->filename);
        else if (redir->type == REDIR_OUT)
            printf("REDIR_OUT: %s\n", redir->filename);
        else if (redir->type == REDIR_APPEND)
            printf("REDIR_APPEND: %s\n", redir->filename);
        else if (redir->type == REDIR_HEREDOC)
        {
            printf("REDIR_HEREDOC: %s\n", redir->filename);
            heredoc_content(redir, depth);
        }
        redir = redir->next;
    }
}

void print_ast(t_ast *ast, int depth)
{
    if (!ast)
        return;
    print_indentation(depth);
    print_node_type(ast);
    if (ast->type == NODE_COMMAND && ast->command)
    {
        print_command_args(ast->command);
        print_redirections(ast->command->redirs, depth);
    }
    else
        printf("\n");
    print_ast(ast->left, depth + 1);
    print_ast(ast->right, depth + 1);
}
