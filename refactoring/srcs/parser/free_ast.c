#include "minishell.h"

void free_ast(t_ast *node)
{
	int i;
    t_redir *redir;
    t_redir *next;

    if (!node)
        return ;
    free_ast(node->left);
    free_ast(node->right);
    if (node->command)
    {
		i = 0;
        while (node->command->argv && node->command->argv[i])
		{
			free(node->command->argv[i]);
			i++;
		}
        free(node->command->argv);
        redir = node->command->redirs;
        while (redir)
        {
            next = redir->next;
            free(redir->filename);
			if (redir->content) 
			{
				free_heredoc_content(redir->content);
				free(redir->content);
			}
				
            free(redir);
            redir = next;
        }
        free(node->command);
    }
    free(node);
}
