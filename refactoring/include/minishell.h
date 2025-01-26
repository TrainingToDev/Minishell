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

//prompt
int	check_args(int argc, char **argv);
char	*format_prompt(void);
char    *prompt_input(char *prompt);

//builtins
int	cd(t_minishell *shell, char **args);
int echo(t_minishell *shell, char **args);
int env(t_minishell *shell, char **args);
int ft_exit(t_minishell *shell, char **args);
int	export(t_minishell *shell, char **args);
int	pwd(t_minishell *shell, char **args);
int unset(t_minishell *shell, char **args);

//lexer
int check_operators(t_token *tokens);
int check_parentheses(t_token *tokens);
int check_redirections(t_token *tokens);
int process_substitution(t_token *token);
int validate_syntax(t_token *tokens);
void	free_token_list(t_token *tokens);
t_token_type invalid_redir(const char *input);
void add_operator_token(t_token **tokens, char *input, size_t *i);
char *extract_quoted_value(char *input, size_t *i, int *expand);
void add_word_token(t_token **tokens, char *input, size_t *i);
int consecutive_redir_in(const char *input);
int	unsupported_redirs(const char *input);
int is_disallowed(t_token *tokens);
int	is_operator(const char *str);
int is_quote(char c);
t_token *create_token(t_token_type type, const char *value, int expand);
t_token_type get_op_token(const char *op);
void	add_token(t_token **tokens, t_token *new_token);
char *extract_word_value(char *input, size_t *i, int *expand);
t_token *lexer(char *input);
void	print_tokens(t_token *tokens);

// expand
char *process_dollar(const char *src, size_t *i, char *result, t_minishell *shell);
char *append_var_value(const char *src, size_t *i, char *result, t_minishell *shell);
char *expand_variables_in_str(const char *src, t_minishell *shell);
char    *compare(char *key, t_env_var *env);
char    *ft_strjoin_free(char *s1, char *s2, int free_flag);
char    *ft_strjoin_char(char *s, char c);
int is_single_quoted(const char *str);
int expand_single_token(t_token *token, t_token *tokens, t_minishell *shell);
void expand_token_list(t_token *tokens, t_minishell *shell);


//parser
t_token	*parser_advance(t_parser *parser);
int	is_token(t_parser *parser, t_token_type type);
char	*clean_quotes(const char *value);
void free_ast(t_ast *node);
t_ast	*parse_list(t_parser *parser, char *input);
t_ast	*create_ast_node(t_node_type type);
t_command *create_cmd(void);
t_redir *create_redir(void);
t_ast *parse_pipe(t_parser *parser, char *input);
t_command *parse_simple_cmd(t_parser *parser, char *input);
t_command *parse_simple_cmd(t_parser *parser, char *input);
t_ast *parse_cmd(t_parser *parser, char *input);
t_redir *parse_io_redirect(t_parser *parser, char *input);
t_ast *parse_subshell(t_parser *parser, char *input);
t_ast *parse_conditional(t_parser *parser, t_ast *left, char *input);
t_ast *parse(t_token *tokens, char *input);
void free_ast(t_ast *ast);
void print_indentation(int depth);
void print_ast(t_ast *ast, int depth);

//execution
int	execute_ast(t_ast *ast, t_minishell *shell);
int is_builtin(const char *cmd_name);
int execute_builtin_cmd(t_command *command, t_minishell *shell);
int execute_external_cmd(t_command *command, t_minishell *shell);
int apply_redirections(t_redir *redirs, t_minishell *shell);
void handle_copied_heredoc(t_hdc *content, const char *delim, t_minishell *shell);
int handle_redir_heredoc(t_redir *current, t_minishell *shell);
char *expand_variables_in_str(const char *src, t_minishell *shell);
char *process_input_line(char *line, const char *delim, t_minishell *shell);
char	**convert_env_list(t_env_var *env_list);
char	*find_command_path(char *cmd_name, t_env_var *env_list);
char *get_path(char **path, char *cmd);
int init_pipe(int pipefd[2]);
int wait_for_children(pid_t pid_left, pid_t pid_right, t_minishell *shell);
pid_t fork_and_exec_left(t_ast *left, int pipefd[2], t_minishell *shell);
pid_t fork_and_exec_right(t_ast *right, int pipefd[2], t_minishell *shell);
void close_pipe_descriptors(int pipefd[2]);
int append_line(t_hdc *content, char *line);
char *read_user_input(const char *delim, t_minishell *shell);
int check_params(t_hdc *content, const char *delim, t_minishell *shell);
void	free_str_array(char **array);

//utils
void free_split(char **split);
void free_heredoc_content(t_hdc *content);
void	print_heredoc_content(const t_hdc *content);
t_hdc	*init_heredoc(void);
char	**split_lines(const char *input);
int	add_line(t_hdc *content, const char *line);
int	get_lines(t_hdc *content, char **lines, const char *delim);
t_hdc	*get_heredoc_lines(const char *input, const char *delim);

void print_env_list(t_env_var *env_list);
void free_env_list(t_env_var *env_list);
int	assign_key_value(t_env_var *env_var, const char *input_env);
void	free_env_var(t_env_var *env_var);
t_env_var	*create_env_var(const char *input_env);
void add_env_var(t_env_var **env_list, t_env_var *new_var);
t_env_var *convert_envp_to_list(char **envp);

void	*print_error(int err_type, char *param, int err);


//signal
int		status_manager(int new_status, int mode);
void	reset_prompt(int sig);
void	main_signals(void);
void	child_signal(int sig);
void	manage_child(void);
void	heredoc_signal(int sig);
void	manage_heredoc(void);
void	main_heredoc(void);



//bonus
int execute_conditional(t_ast *ast, t_minishell *shell);
pid_t create_subshell_process(t_ast *ast, t_minishell *shell);
int wait_for_subshell(pid_t pid, t_minishell *shell);
int validate_subshell_node(t_ast *ast);

#endif