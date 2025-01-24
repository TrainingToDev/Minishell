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

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "sys/stat.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "libft/libft.h"

typedef struct s_token
{
    char *token;
    int state;
    int check;
    struct s_token *next;
}               t_token;

typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
}               t_env;

typedef struct s_export
{
    char *proto;
    char *var;
    char *value;
    struct s_export *next;
}               t_export;

typedef struct s_shell
{
    t_env *env;
    t_export *exp;
    t_list *built;
}               t_shell;

//for the env_list && exp_list

void    add_new_exp(t_export **lst, t_export *new);
void	add_new_env(t_env **lst, t_env *new);
int is_space (int c);
int is_alpha(int c);
int is_alphasymb(int c);
int check_pipe(char *input);
t_env	*get_env(char **env);
t_export    *get_export_list(char **env);
t_export    *new_export(char *env, int i);
t_env	*new_env(char *env, int state);
char	*get_string(char *env, int i, int len, int c);
char    *reform(char *old);

//builtins

int echo_command(t_token **token);
int env_command(t_env *env, t_token **token);
int pwd_command(t_token **token);
int export_command(t_env *env, t_token **token, t_export *exp);
int unset_command(t_env *env, t_export *exp,t_token **token);


//parsing

typedef struct s_quote
{
    int lock;
    int simple;
    int duo;
}               t_quote;

int valid_pipe(char *input);//number of valid quote
int quote_number(char *argv);//number of quote in a 
char **get_pile(char *input);//get the pile of execution
int get_number_of(char *input, int c);
char *change(char *input);//manala ilay espace @ redirection
char **input_file(char *input);
char **output_file(char *input);
int chech_space(char *input);

//expand
int case_quote(char *input, int i);
char *new_expand(char *input, t_shell *shell);

//get_token
char **tokening(char *input);
void    add_new_token(t_token **tok, t_token *new);
t_token *g_token(char *token);
t_token **get_all_token(char **data, int len);
int is_alphanum(int c);
int quote_case(char *input, int i);
int pipe_void(char *input);
int test2(char *input, int i);
int test1(char *input, int i);
int test3(char *input, int i);
int test4(char *input, int i);
int check_redir(char *input);
char *reform_simple(char *tok);
char *reform_double(char *tok);

//token_state 
//-1:error
//1:command
//2:redirection file
//3:eof de heredoc
//4:input file
//5:output file
//6:argument

t_token    **get_all_state(t_token **all);
void    command (t_token **tok);
void    is_redir(t_token **tok);
void    is_heredoc(t_token **tok);
void    is_input_file(t_token **tok);
void    is_output_file(t_token **tok);
void    is_argument(t_token **tok);


//PIPE AND EXEC
//void    create_fils(t_token **all, int pipe_nbr);
int is_builtins(t_token **tok, t_list *built);
t_list *get_all_builtins();
void state_command(t_token **token, t_shell *shell);
void create_fork(t_token **tok, int nbr_pipe, t_shell *shell);
void pipe_implemantations(t_token **tok, int nbr_exc,t_shell *shell);
void exact_builtin(t_token **token,t_shell *shell, int command_id);
void pipe_command(t_token **tok, t_shell *shell, int index, int **fd);
char *get_path(t_token **token, t_env *env);
char **form_env(t_env *env, int len);
int env_len(t_env *env);

//get_off_quote
int count_quote(char *command);
char *get_off_quote(char *old, int count);

//builtins utils
void take_all_quote(t_token **tok);
int checking_redir(t_token *temp);
char *get_var(char *tok);
char *get_value(char *tok);
int existing(char *var, t_export *exp);
int exist_env(char *var, t_env *exp);
int is_option(char *arg);
int all_num(char *in);

//execve utils
char **get_all_path(t_env *env);
char *real_dir(char **path, char *cmd);
int env_len(t_env *env);
char **get_arg(t_token *tok, int len);
int len_arg(t_token *tok);
int new_proc(t_token **tok, t_shell *shell);

//free_function 
void ft_free(char **splitted);
void free_token (t_token *tok);
void free_env(t_env *env);
void free_exp(t_export *env);
void free_fd(int **fd);
void free_exec(t_token **tok);
void free_list(t_list *list);
void free_ft(t_token **tok, t_shell *shell);

#endif