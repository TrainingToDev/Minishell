/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:50:28 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/31 11:39:30 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <limits.h>

# define COLOR_RESET "\033[0m"
# define COLOR_GREEN "\033[32m"
# define COLOR_BLUE "\033[34m"
# define COLOR_RED "\033[31m"

# define STATUS_READ 0
# define STATUS_WRITE 1
# define STATUS_QUIT 2
# define STATUS_INIT 3

# define SUCCESS 0
# define ERR_G 1
# define ERR_SYN 2
# define ERR_DIR 126
# define ERR_CMD 127
# define ERR_SIGINT 130
# define ERR_SEGV 131

# define MSG_1 "minishell: warning: here-document at line"
# define MSG_2 "delimited by end-of-file (wanted `"
# define MSG_3 "')\n"

extern volatile sig_atomic_t g_status;

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
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	int					expand;
	struct s_token		*next;
}						t_token;

typedef struct s_hdc
{
	char				**lines;
	size_t				count;
}						t_hdc;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_INVALID
}						t_redir_type;

typedef struct s_redir
{
	t_redir_type		type;
	char				*filename;
	t_hdc				*content;
	struct s_redir		*next;
}						t_redir;

typedef struct s_parser
{
	t_token				*current;
}						t_parser;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}						t_node_type;

typedef struct s_ast
{
	t_node_type			type;
	struct s_command	*command;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef struct s_command
{
	char				**argv;
	int					argc;
	t_redir				*redirs;
}						t_command;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_minishell
{
	t_env_var			*env_list;
	int					last_exit_status;
	t_token				*tokens;
	t_ast				*ast;
	int					nb_line_heredoc;
	int					running;
	int					fd_input;
	int					fd_output;
}						t_minishell;

enum	e_mini_error
{
	E_QUOTE = 1,
	E_SYNTAX = 2,
	E_DIR = 3,
	E_CMD = 4,
	E_DUPFD = 5,
	E_FORK = 6,
	E_PIPE = 7,
	E_NOMEM = 8,
	E_VAR = 9,
	E_VAR_O = 10,
	E_SUP = 11,
	E_EXIT = 12,
	E_WARNING = 13
};

// expand struct
typedef struct s_varinfo
{
	const char			*src;
	size_t				start;
	size_t				len;
}						t_varinfo;

typedef struct s_state
{
	size_t	index;
	int		single_quote;
	int		double_quote;
}			t_state;

// prompt
int						check_args(int argc, char **argv);
char					*format_prompt(void);
char					*prompt_input(char *prompt);

// builtins
int						cd(t_minishell *shell, char **args);
int						echo(t_minishell *shell, char **args);
int						env(t_minishell *shell, char **args);
int						ft_exit(t_minishell *shell, char **args);
int						export(t_minishell *shell, char **args);
int						pwd(t_minishell *shell, char **args);
int						unset(t_minishell *shell, char **args);
int						is_builtin(const char *cmd_name);
int						execute_builtin(t_minishell *shell, char **args);

// cd_utils
char					*get_env_cd(const char *key, t_env_var *env_list);
int						update_env_value_if_exists(t_env_var *env_list,
							const char *key, const char *value);
t_env_var				*create_new_env_node(const char *key,
							const char *value);
void					append_env_node(t_env_var **env_list,
							t_env_var *new_node);
void					set_env_value(t_env_var **env_list, const char *key,
							const char *value);

//export_utils
int			is_valid_id(const char *str);
void		sort_array(t_env_var **env_array, int count);
int			count_vars(t_env_var *env_list);
t_env_var	**create_array(t_env_var *env_list, int count);
t_env_var	*new(char *key, char *value, t_env_var *current);
void		display_exported(t_minishell *shell);
int			export_error(char *arg);
t_env_var	*find_pos(t_env_var *env_list, char *key, t_env_var **prev);
void		update_env(t_minishell *shell, char *key, char *value);
int			export_arg(t_minishell *shell, char *arg);
void		fast_export(t_token *tokens, t_minishell *shell);
void 		fast_unset(t_token *tokens, t_minishell *shell);
void		remove_env_var(t_minishell *shell, const char *key);

// lexer
int				check_operators(t_token *tokens);
int				check_parentheses(t_token *tokens);
int				is_disallowed(t_token *tokens);
int				process_substitution(t_token *token);
int				check_redirections(t_token *tokens);
int				validate_syntax(t_token *tokens);
int				consecutive_redir_in(const char *input);
int				unsupported_redirs(const char *input);
int				is_operator(const char *str);
int				is_quote(char c);
void			add_operator_token(t_token **tokens, char *input, size_t *i);
void			add_word_token(t_token **tokens, char *input, size_t *i);
void			add_token(t_token **tokens, t_token *new_token);
char			*extract_word_value(char *input, size_t *i, int *expand);
char			*extract_quoted_value(char *input, size_t *i, int *expand);
t_token_type	invalid_redir(const char *input);
t_token_type	get_op_token(const char *op);
t_token			*create_token(t_token_type type, const char *value, int expand);
t_token			*lexer(char *input);
char			*check_close(char *input, int *open_count);
void			free_token_list(t_token *tokens);
void			print_tokens(t_token *tokens);

// expander
char			*join_exit_status(char *res, t_minishell *shell);
char			*add_char(char *src, size_t *i, char *res);
char			*proc_dlr(char *src, size_t *i, char *res, t_minishell *shell);
char			*add_vval(char *src, size_t *i, char *result, t_minishell *shell);
char			*scan_token(char *src, t_state *s, char *res, t_minishell *shell);
char			*expand_var(char *src, t_minishell *shell);
void			expand_token_list(t_token *tokens, t_minishell *shell);
void			mark_heredoc_delimiters(t_token *tokens);

// utils expander
char			*compare(char *key, t_env_var *env);
char			*join_free(char *s1, char *s2, int free_flag);
char			*concat_char(char *s, char c);
int				is_single_quoted(const char *str);

// parser
t_ast			*parse_list(t_parser *parser, char *input);
t_ast			*create_ast_node(t_node_type type);
t_ast			*parse_pipe(t_parser *parser, char *input);
t_ast			*parse_cmd(t_parser *parser, char *input);
t_ast			*parse_subshell(t_parser *parser, char *input);
t_ast			*parse_conditional(t_parser *parser, t_ast *left, char *input);
t_ast			*parse(t_token *tokens, char *input);

t_command		*create_cmd(void);
t_command		*parse_simple_cmd(t_parser *parser, char *input);
t_command		*parse_simple_cmd(t_parser *parser, char *input);

t_redir			*create_redir(void);
t_redir			*parse_io_redirect(t_parser *parser, char *input);

t_token			*parser_advance(t_parser *parser);

int				is_token(t_parser *parser, t_token_type type);
char			*clean_quotes(const char *value);

void			free_ast(t_ast *ast);
void			print_indentation(int depth);
void			print_ast(t_ast *ast, int depth);

// execution
int						execute_builtin_cmd(t_command *command, t_minishell *shell,
							int fork_required);
int						execute_extern_cmd(t_command *command,
							t_minishell *shell);
int						execute_ast(t_ast *ast, t_minishell *shell);
int						execute_command(t_command *command, t_minishell *shell, 
							int fork_required);
int						dir_error(char *path);
void					exec_child(char *path, t_command *cmd, t_minishell *shell, int f);
int						exec_parent(pid_t pid, t_minishell *shell);
int						valid_cmd_name(t_command *cmd);

// redir
int 			apply_redir(t_redir *redirs, t_minishell *shell, int mode, int f);
int 			apply_builtins_redir(t_redir *redirs, t_minishell *shell);
int 			process_redir_in(t_redir *current, int mode);
int 			process_redir_out(t_redir *current, int mode);
int				process_redir_append(t_redir *current, int mode);
int				process_heredoc(t_redir *cur, t_minishell *shell, int mode, int f);
int				forked_heredoc(t_hdc *cnt, char *dlim, t_minishell *shell, int c);
int				exit_input(t_redir *redirs);
void			exit_output(t_redir *redirs);

// heredoc
int						check_params(t_hdc *cnt, char *dlim,
							t_minishell *shell);
char					*read_user_input(char *dlim, t_minishell *shell);
int						insert_line(t_hdc *cnt, char *line);
char					*trim_quotes(char *str);
void					heredoc_interactive(char *dlim, t_hdc *cnt,
							t_minishell *shell);
void					heredoc_copied(t_hdc *cnt, char *dlim,
							t_minishell *shell);

// env
char					**convert_env_list(t_env_var *env_list);

// find_path
char					*find_command_path(char *cmd_name, t_env_var *env_list);
void					free_str_array(char **array);

// pipe
int						init_pipe(int pipefd[2]);
int						wait_for_children(pid_t pid_left, pid_t pid_right);
pid_t					fork_and_exec_left(t_ast *left, int pipefd[2],
							t_minishell *shell);
pid_t					fork_and_exec_right(t_ast *right, int pipefd[2],
							t_minishell *shell);
void					close_pipe_descriptors(int pipefd[2]);

// utils
void					free_split(char **split);
void					free_heredoc_content(t_hdc *cnt);
char					**split_lines(char *input);
t_hdc					*init_heredoc(void);
t_hdc					*get_heredoc_lines(char *input, char *dlim);
int						add_line(t_hdc *cnt, char *line);
int						get_lines(t_hdc *cnt, char **lines, char *dlim);

// environment
void					print_env_list(t_env_var *env_list);
void					free_env_list(t_env_var *env_list);
t_env_var				*convert_envp_to_list(char **envp);
void	free_env_var(t_env_var *env_var);

// signal
int						status_manager(int new_status, int mode);
void					setup_signals(void);
void					manage_heredoc(void);
void					setup_child(void);
void					reset_main(void);
void					del(void);

// manage error
void					*print_error(int err_type, char *param, int err);

//clean shell
void					cleanup_shell(t_minishell *shell);

// bonus
int						execute_conditional(t_ast *ast, t_minishell *shell);
int						execute_subshell(t_ast *ast, t_minishell *shell);

#endif
