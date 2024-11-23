#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../srcs/lexer/lexer.c"
#include "../srcs/lexer/init_token.c"
#include "../srcs/lexer/manage_token.c"
#include "../srcs/parser/parser.c"
#include "../srcs/parser/node.c"
#include "../srcs/utils/free.c"
#include "../srcs/utils/prints.c"
#include "../srcs/utils/utils.c"
/* #include "../srcs/utils/prompt.c"
#include "../srcs/utils/environment.c"
#include "../srcs/signals/signals.c" */
#include "minishell.h"


// for test
void    print_ast(t_ast *ast, int depth)
{
	int i;

	if (!ast)
		return;
	i = 0;
	while(i < depth)
	{
		printf("  ");
		i++;
	}
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
	if (ast->type == NODE_COMMAND && ast->command)
	{
		printf("[ ");
		int i = 0;
		while ( i < ast->command->argc)
		{
			printf("%s ", ast->command->argv[i]);
			i++;
		}
		printf("]\n");

		t_redirection *redir = ast->command->redirs;
		while (redir)
		{
			int i = 0;
			while ( i < depth + 1)
			{
				printf("  ");
				i++;
			}
			if (redir->type == REDIR_IN)
				printf("REDIR_IN: %s\n", redir->filename);
			else if (redir->type == REDIR_OUT)
				printf("REDIR_OUT: %s\n", redir->filename);
			else if (redir->type == REDIR_APPEND)
				printf("REDIR_APPEND: %s\n", redir->filename);
			else if (redir->type == REDIR_HEREDOC)
				printf("REDIR_HEREDOC: %s\n", redir->filename);
			redir = redir->next;
		}
	}
	else
		printf("\n");
	print_ast(ast->left, depth + 1);
	print_ast(ast->right, depth + 1);
}

// gcc -Wall -Wextra -Werror ./test_parser.c -I../include ../libft/libft.a -lreadline

int main(void)
{
	char    *input;
	t_token *tokens;
	t_ast   *ast;

	printf("Welcome to the parser tester! Type 'exit' to quit.\n");

	while (1)
	{
		input = readline("Test> ");
		if (!input || strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		add_history(input);
		tokens = lexer(input);
		if (!tokens)
		{
			printf("Lexer error: Unable to tokenize input.\n");
			free(input);
			continue ;
		}
		print_tokens(tokens);
		ast = parser(&tokens);
		if (!ast)
		{
			printf("Parser error: Unable to create AST.\n");
			free_tokens(tokens);
			free(input);
			continue;
		}
		printf("Abstract Syntax Tree (AST):\n");
		print_ast(ast, 0);

		free_ast(ast);
		free_tokens(tokens);
		free(input);
	}
	printf("Goodbye!\n");
	return 0;
}

