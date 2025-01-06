#ifndef MINISHELL_H
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

# define COLOR_RESET "\033[0m"
# define COLOR_GREEN "\033[32m"
# define COLOR_BLUE  "\033[34m"
# define COLOR_RED   "\033[31m"


#define STATUS_READ 0
#define STATUS_WRITE 1


typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_UNKNOWN,
}   t_token_type;

typedef struct s_token
{
	char            *value;
	t_token_type    type;
	int             expand;
	struct s_token  *next;
}   t_token;

typedef struct s_hdc
{
	char	**lines;
	size_t	count;
}			t_hdc;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}   t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	t_hdc			*content;
	struct s_redir	*next;
}   t_redir;

typedef enum e_node_type
{
	NODE_COMMAND, 
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}   t_node_type;

typedef struct s_ast
{
	t_node_type       type;
	struct s_command  *command;
	t_token_type      operator;
	struct s_ast      *left;
	struct s_ast      *right;
}   t_ast;


typedef struct s_command
{
	char			**argv;
	int				argc;
	t_redir			*redirs;
}					t_command;

typedef struct s_env_var
{
	char                *key;
	char                *value;
	struct s_env_var    *next;
}						t_env_var;

typedef struct s_minishell
{
	t_env_var   *env_list;
	int         last_exit_status; //$?
	int         interactive;
	int         original_stdin;
    int         original_stdout;
    int         original_stderr;
}				t_minishell;



enum	e_mini_error
{
	E_QUOTE = 1,          // syntax Unclosed quote
	E_NODIR = 2,          // Aucun répertoire trouvé
	E_PDENIED = 3,         // Permission refusée
	E_NOCMD = 6,          // Command not found
	E_DUPFD = 7,          // dupplication fd failed
	E_FORK = 8,           // fork failed
	E_PIPE = 9,           // pipe failed
	E_SYNTAX = 10,       // syntax error near unexpected token
	E_NOMEM = 11,         // Erreur d'allocation mémoire
	E_ISDIR = 12,         // Fichier spécifié est un répertoire
	E_NOTDIR = 13,        // Not a directory
	E_WARNING = 14        // Avertissement général
};

t_token			*lexer(char *input);
char			*extract_word_value(char *input, size_t *i, int *expand);
char			*extract_quoted_value(char *input, size_t *i, int *expand);
t_token			*create_token(t_token_type type, const char *value, int expand);
void			add_token(t_token **tokens, t_token *new_token);
void			add_word_token(t_token **tokens, char *input, size_t *i);
t_token_type	get_op_token(const char *str);
t_token_type	invalid_redir(const char *input);
int				is_operator(const char *str);
int				is_quote(char c);
int				validate_syntax(t_token *tokens);
int				check_operators(t_token *tokens);
int				check_redirections(t_token *tokens);
int				check_parentheses(t_token *tokens);
int				check_args(int argc, char **argv);
char			*format_prompt(void);

void			*print_error(int err_type, char *param, int err);

void			setup_signals(void);
int				status_manager(int new_status, int mode);

void			free_token_list(t_token *tokens);
void			free_split(char **split);
void			free_heredoc_content(t_hdc *content);

t_hdc			*get_heredoc_lines(const char *input, const char *delimiter);
int				get_lines(t_hdc *content, char **lines, const char *delimiter);
int				add_line(t_hdc *content, const char *line);

void			print_tokens(t_token *tokens);


char *compare(char *var, t_env *env);


#endif



