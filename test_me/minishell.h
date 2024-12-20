/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:24:34 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 08:40:24 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <ctype.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>
# include <limits.h>

# define RUN 1

// color for prompt
# define COLOR_RESET "\033[0m"
# define COLOR_GREEN "\033[32m"
# define COLOR_BLUE  "\033[34m"
# define COLOR_RED   "\033[31m"


// define only global for signal
//here


// struct for type of tokens
typedef enum e_token_type
{
	TOKEN_WORD, // (cmd, args)
	TOKEN_PIPE, // |
	TOKEN_REDIRECT_IN, // <
	TOKEN_REDIRECT_OUT, // >
	TOKEN_APPEND, // >>
	TOKEN_HEREDOC, // <<
	TOKEN_AND, // &&
	TOKEN_OR, // ||
	TOKEN_LPAREN, // '('
	TOKEN_RPAREN, // ')'
	TOKEN_EOF,
	TOKEN_UNKNOWN // not define
}   t_token_type;

// struct manage for tokenization (Lexical Analyser)
typedef struct s_token
{
	char            *value;
	t_token_type    type;
	int             expand;
	struct s_token  *next;
}   t_token;

// struct for type of redirections
typedef enum e_redir_type
{
	REDIR_IN,        // '<'
	REDIR_OUT,       // '>'
	REDIR_APPEND,    // '>>'
	REDIR_HEREDOC    // '<<'
}   t_redir_type;

// struct manage redirections
typedef struct s_redirection
{
	t_redir_type             type;
	char                     *filename;
	struct s_redirection     *next;
}   t_redirection;

// struct for type AST
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND, // &&
	NODE_OR, // ||
	NODE_LOGICAL, // manage logical for cmd
	NODE_SUBSHELL // manage brackets
}   t_node_type;

// struct for building AST
typedef struct s_ast
{
	t_node_type       type;
	struct s_command  *command;
	t_token_type      operator;
	struct s_ast      *left;
	struct s_ast      *right;
}   t_ast;

// struct for cmd
typedef struct s_command
{
	char                **argv;
	int                 argc;
	t_redirection       *redirs;
}   t_command;

// struct for environment variable
typedef struct s_env_var
{
	char                *key;
	char                *value;
	struct s_env_var    *next;
}   t_env_var;

// struct for minishell
typedef struct s_minishell
{
	t_env_var   *env_list;
	int         last_exit_status;
	int         interactive;
}   t_minishell;


// prototype buildins

int			is_builtin(const char *cmd_name);
int			execute_builtin(t_minishell *shell, t_command *cmd);
int         builtin_echo(t_minishell *shell, char **args);
int         builtin_cd(t_minishell *shell, char **args);
int         builtin_pwd(t_minishell *shell, char **args);
int         builtin_export(t_minishell *shell, char **args);
int         builtin_unset(t_minishell *shell, char **args);
int         builtin_env(t_minishell *shell, char **args);
int         builtin_exit(t_minishell *shell, char **args);


// test function
char	*get_command_path(char *cmd, char **envp);
void	free_split(char **split);
void	ft_error(const char *message, int exit_code);
void 	exit_cmd(char *input);
void	print_error_message(char *shell, int errnum, char *filename);
void	change_directory(const char *path);

// implemetation function for minishell

t_token	*create_token(t_token_type type, const char *value, int expand);
void	add_token(t_token **tokens, t_token *new_token);
void	add_operator_token(t_token **tokens, const char *input, size_t *i);
void	add_quoted_token(t_token **tokens, const char *input, size_t *i);
void	add_word_token(t_token **tokens, const char *input, size_t *i);

t_token_type get_operator_token_type(const char *str);
char		*extract_quoted_value(const char *input, size_t *i, int *expand);
char		*extract_word_value(const char *input, size_t *i);

//utils
void add_to_history(const char *input);
int init_minishell(t_minishell *shell, char **envp);
int minishell_loop(t_minishell *shell);
int is_operator(const char *str);
int is_quote(char c);



//...



#endif
