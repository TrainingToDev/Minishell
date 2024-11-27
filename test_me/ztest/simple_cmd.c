#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "../lexer/lexer.c"
#include "../lexer/init_token.c"
#include "../lexer/manage_token.c"
#include "../utils/utils.c"
#include "../utils/prints.c"


void free_tokens(t_token *tokens);
void free_ast(t_ast *ast);
void print_ast(t_ast *ast, int depth);

t_ast	*create_ast_node(t_node_type type, t_command *cmd)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		display_error("Memory allocation failed for AST node");
		return	(NULL);
	}
	node->type = type;
	node->command = cmd;
	node->operator = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_redirection *init_redir(t_token_type type)
{
	t_redirection *redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	if (type == TOKEN_REDIRECT_IN)
		redir->type = REDIR_IN;
	else if (type == TOKEN_REDIRECT_OUT)
		redir->type = REDIR_OUT;
	else if (type == TOKEN_APPEND)
		redir->type = REDIR_APPEND;
	else if (type == TOKEN_HEREDOC)
		redir->type = REDIR_HEREDOC;
	return (redir);
}

void add_redir(t_redirection **current, t_redirection *redir)
{
	while (*current)
		current = &((*current)->next);
	*current = redir;
	redir->next = NULL;
}

int validate_redir(t_token **tokens, t_redirection *redir)
{
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		display_syntax_error("syntax error: Expected file or delimiter after redirection");
		free(redir);
		return (0);
	}
	redir->filename = ft_strdup((*tokens)->value);
	if (!redir->filename)
	{
		free(redir);
		return (0);
	}
	*tokens = (*tokens)->next;
	return (1);
}




/* 
int parse_redirections(t_token **tokens, t_command *cmd)
{
	t_redirection *redir;
	t_redirection **current;

	current = &cmd->redirs;

	while (*tokens && is_redirection_token((*tokens)->type))
	{
		redir = init_redir((*tokens)->type);
		if (!redir)
			return (0);
		*tokens = (*tokens)->next;
		if (!validate_redir(tokens, redir))
			return (0);
		add_redir(current, redir);
	}
	return (1);
} */

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

void free_redirections(t_redirection *redirs)
{
    t_redirection *tmp;

    while (redirs)
    {
        tmp = redirs;
        redirs = redirs->next;
        free(tmp->filename);
        if (tmp->type == REDIR_HEREDOC)
            free(tmp->content);
        free(tmp);
    }
}



/* void free_redirections(t_redirection *redirs)
{
	t_redirection *tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		free(tmp->filename);
		free(tmp);
	}
} */

void free_string_array(char **array)
{
	int i = 0;

	if (!array)
		return;
	while (array[i])
		free(array[i++]);
	free(array);
}

void free_command(t_command *cmd)
{
	if (!cmd)
		return;
	free_string_array(cmd->argv);
	free_redirections(cmd->redirs);
	free(cmd);
}


t_ast *free_command_with_error(t_command *cmd)
{
	printf("missing cmd\n");
	free_command(cmd);
	return (NULL);
}

int validate_command(t_command *cmd)
{
	if (cmd->argc == 0 && cmd->redirs == NULL)
	{
		display_syntax_error("syntax error: Missing command");
		return (0);
	}
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


/* t_ast *parse_simple_command(t_token **tokens)
{
	t_command *cmd;
	t_ast *ast;

	cmd = init_command();
	if (!cmd)
		return NULL;
	while (*tokens && is_redirection_token((*tokens)->type))
	{
		if (!parse_redirections(tokens, cmd))
		{
			free_command(cmd);
			return (NULL);
		}
	}
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		if (!add_argument(cmd, (*tokens)->value))
		{
			free_command(cmd);
			return (NULL);
		}
		*tokens = (*tokens)->next;
	}
	while (*tokens && is_redirection_token((*tokens)->type))
	{
		if (!parse_redirections(tokens, cmd))
		{
			free_command(cmd);
			return (NULL);
		}
	}
	if (cmd->argc == 0 && cmd->redirs == NULL)
	{
		display_syntax_error("syntax error: Missing command");
		free_command(cmd);
		return (NULL);
	}
	ast = create_ast_node(NODE_COMMAND, cmd);
	if (!ast)
	{
		free_command(cmd);
		return (NULL);
	}
	return (ast);
} */
//for test
int simulate_heredoc(const char *delimiter)
{
    char *line = NULL;
    char *token = NULL;
    int pipe_fd[2];


    if (pipe(pipe_fd) == -1)
    {
        perror("minishell: Error creating heredoc pipe");
        return (-1);
    }
    while ((line = readline("> ")))
    {
        token = strtok(line, "\n");
        while (token)
        {
            if (strcmp(token, delimiter) == 0)
            {
                free(line);
                close(pipe_fd[1]);
                return (pipe_fd[0]);
            }
            if (write(pipe_fd[1], token, strlen(token)) == -1 ||
                write(pipe_fd[1], "\n", 1) == -1)
            {
                perror("minishell: Error writing to heredoc pipe");
                free(line);
                close(pipe_fd[1]);
                close(pipe_fd[0]);
                return (-1);
            }

            token = strtok(NULL, "\n");
        }

        free(line);
    }

    // EOF inattendu
    write(STDERR_FILENO, "minishell: warning: here-document delimited by EOF (wanted `", 57);
    write(STDERR_FILENO, delimiter, strlen(delimiter));
    write(STDERR_FILENO, "`)\n", 3);

    close(pipe_fd[1]);
    return (pipe_fd[0]);
}



char *collect_heredoc_content(t_token **tokens, char *delimiter)
{
    char *content = ft_strdup("");
    char *temp;
    while (*tokens)
    {
        if ((*tokens)->type == TOKEN_WORD && strcmp((*tokens)->value, delimiter) == 0)
        {
            *tokens = (*tokens)->next;
            break;
        }
        temp = ft_strjoin(content, (*tokens)->value);
        temp = ft_strjoin(temp, "\n");
        free(content);
        content = temp;
        *tokens = (*tokens)->next;
    }
    return content;
}



int parse_redirections(t_token **tokens, t_command *cmd)
{
    t_redirection *redir;
    t_redirection **current;

    current = &cmd->redirs;

    while (*tokens && is_redirection_token((*tokens)->type))
    {
        redir = init_redir((*tokens)->type);
        if (!redir)
            return (0);
        *tokens = (*tokens)->next;
        if (!validate_redir(tokens, redir))
            return (0);
        if (redir->type == REDIR_HEREDOC)
        {
            redir->content = collect_heredoc_content(tokens, redir->filename);
            if (!redir->content)
            {
                free(redir);
                return (0);
            }
        }
        add_redir(current, redir);
    }
    return (1);
}




void execute_command(t_command *cmd)
{
    t_redirection *redir = cmd->redirs;

    // Gérer les redirections
    while (redir)
    {
        int fd = -1;

        if (redir->type == REDIR_HEREDOC) // Gestion pour <<
        {
			int pipe_fd[2];
            if (pipe(pipe_fd) == -1)
            {
                perror("minishell: Error creating heredoc pipe");
                exit(1);
            }
            write(pipe_fd[1], redir->content, strlen(redir->content));
            close(pipe_fd[1]);
            if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
            {
                perror("minishell: Error redirecting input");
                close(pipe_fd[0]);
                exit(1);
            }
            close(pipe_fd[0]);
        }
        else if (redir->type == REDIR_IN) // Gestion pour <
        {
            fd = open(redir->filename, O_RDONLY);
            if (fd == -1)
            {
                perror("minishell: Error opening input file");
                exit(1);
            }
        }
        else if (redir->type == REDIR_OUT) // Gestion pour >
        {
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("minishell: Error opening output file");
                exit(1);
            }
        }
        else if (redir->type == REDIR_APPEND) // Gestion pour >>
        {
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("minishell: Error opening output file in append mode");
                exit(1);
            }
        }

        if (fd != -1)
        {
            if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
            {
                if (dup2(fd, STDIN_FILENO) == -1)
                {
                    perror("minishell: Error redirecting input");
                    close(fd);
                    exit(1);
                }
            }
            else // REDIR_OUT ou REDIR_APPEND
            {
                if (dup2(fd, STDOUT_FILENO) == -1)
                {
                    perror("minishell: Error redirecting output");
                    close(fd);
                    exit(1);
                }
            }
            close(fd);
        }

        redir = redir->next;
    }

    if (execvp(cmd->argv[0], cmd->argv) == -1)
    {
        perror("minishell: Command execution failed");
        exit(1);
    }
}





void execute_ast(t_ast *ast)
{
    if (!ast)
        return;

    if (ast->type == NODE_COMMAND)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
           //process child
            execute_command(ast->command);
        }
        else if (pid > 0)
        {
            // Process parent
            int status;
            waitpid(pid, &status, 0);
        }
        else
        {
            perror("minishell: fork");
        }
    }
    else
    {
        fprintf(stderr, "Unsupported AST node type\n");
    }
}


// gcc -Wall -Wextra -Werror -I../include simple_cmd.c ../libft/libft.a -lreadline

int main(void)
{
	char *input;
	t_token *tokens;
	t_ast *ast;

	printf("Test individual for simple cmd. exit for log out.\n");

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
			printf("Error lexer : Impossible to tokenised input.\n");
			free(input);
			continue;
		}

		print_tokens(tokens);

		ast = parse_simple_command(&tokens);
		if (!ast)
		{
			printf("Erreur du parser : Impossible to create AST for input : %s\n", input);
			free_tokens(tokens);
			free(input);
			continue;
		}

		printf("Arbre syntaxique abstrait (AST) :\n");
		print_ast(ast, 0);

		printf("----------------\n");

		execute_ast(ast);

		free_ast(ast);
		free_tokens(tokens);
		free(input);
	}

	printf("Au revoir !\n");
	return 0;
}

void free_tokens(t_token *tokens)
{
	while (tokens)
	{
		t_token *next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

void free_ast(t_ast *ast)
{
	if (!ast)
		return;

	if (ast->type == NODE_COMMAND)
		free_command(ast->command);

	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
}

void print_ast(t_ast *ast, int depth)
{
	if (!ast)
		return;

	for (int i = 0; i < depth; i++)
		printf("  "); // Indentation

	if (ast->type == NODE_COMMAND)
	{
		printf("NODE_COMMAND: ");
		if (ast->command)
		{
			printf("[ ");
			for (int i = 0; i < ast->command->argc; i++)
				printf("%s ", ast->command->argv[i]);
			printf("]\n");

			t_redirection *redir = ast->command->redirs;
			while (redir)
			{
				for (int i = 0; i < depth + 1; i++)
					printf("  ");
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
	}
	else
	{
		printf("UNKNOWN NODE\n");
	}

	if (ast->left)
		print_ast(ast->left, depth + 1);
	if (ast->right)
		print_ast(ast->right, depth + 1);
}


