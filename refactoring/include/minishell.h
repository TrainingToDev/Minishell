/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:50:28 by miaandri          #+#    #+#             */
/*   Updated: 2024/12/07 04:39:14 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <stdbool.h>

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
	REDIR_HEREDOC,
	REDIR_INVALID
}   t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	t_hdc			*content;
	struct s_redir	*next;
}   t_redir;

// Manage Tokens
typedef struct s_parser
{
    t_token *current;
} t_parser;


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
    t_env_var   *env_list;         // Liste chaînée des variables d'environnement
    int         last_exit_status; // Dernier code de retour (important pour `$?`)
    t_token     *tokens;          // Liste chaînée des tokens générés par le lexer
    t_ast       *ast;             // Arbre syntaxique pour la commande actuelle
    int			nb_line_heredoc;  // compteur pour heredoc
	int         running;          // Indique si le shell est en cours d'exécution (utile pour les boucles)
    int         fd_input;         // Descripteur d'entrée standard (utilisé pour redirections)
    int         fd_output;        // Descripteur de sortie standard (utilisé pour redirections)
}               t_minishell;

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

// expand
typedef struct s_varinfo
{
    const char *src;
    size_t      start;
    size_t      len;
}   t_varinfo;


t_ast *parse_pipe(t_parser *parser, char *input);
t_ast *parse_cmd(t_parser *parser, char *input);
t_ast *parse_conditional(t_parser *parser, t_ast *left, char *input);
t_ast *parse_subshell(t_parser *parser, char *input);
t_command *parse_simple_cmd(t_parser *parser, char *input);
t_redir *parse_io_redirect(t_parser *parser, char *input);
t_ast *parse(t_token *tokens, char *input);
void free_ast(t_ast *ast);

int	execute_ast(t_ast *ast, t_minishell *shell);

//execution
int	execute_ast(t_ast *ast, t_minishell *shell);
int is_builtin(const char *cmd_name);
int execute_builtin_cmd(t_command *command, t_minishell *shell);
int execute_external_cmd(t_command *command, t_minishell *shell);
int apply_redirections(t_redir *redirs, t_minishell *shell);
char	**convert_env_list(t_env_var *env_list);
char	*find_command_path(char *cmd_name, t_env_var *env_list);

#endif