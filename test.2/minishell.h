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
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "libft/libft.h"

typedef struct s_expand//used at the expand function
{
    int start;
    int len;
}               t_expand;

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
    t_env *env;
}               t_export;

extern int g_sign;
void	add_new_env(t_env **lst, t_env *new);
int exact_command(char *data, char *command);
int is_alpha(int c);
int is_alphasymb(int c);
int is_variable(char *string);
int list_size(t_env *env);
int check_pipe(char *input);
t_env	*get_env(char **env);
t_env	*new_env(char *env);
//char	*get_string(char *env, int i, int len, int c);

//builtins

int echo_command(t_token **token);
int env_command(t_env *env, t_token **token);
int pwd_command(t_token **token);


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

//expand
char **split_expand(char *input);
int case_quote(char *input, int i);
char **secund_split(char *split, t_env *env);
char *expand(char **splitted);
int change2(char *splitted);
int count(char *split);

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


//test_token
//1:command
//2:fichier de redirection sans le signe de redirection
//-20:fichier de redirection (avec le signe de redirection)avec autes redirection dans le token 
//20:fichier de redirection (sans le signe de redirection)avec autes redirection dans le token
//-2:fichier de redirection avec le signe de redirection
//3:eof de heredoc sans signe de heredoc
//30:eof de heredoc avec d'autres caracteres de redirection (sans le signe de heredoc)
//-30:eof de heredoc avec d'autres caracteres de redirection (avec le signe de heredoc)
//-3:eof de heredoc avec signe de heredoc
//4:input sans signe
//40:input avec d'autres caracteres de redirection (sans le signe de input)
//-40:input avec d'autres caracteres de redirection (avec le signe de input)
//-4:input avec signe
//5:output sans signe
//50:output avec d'autres caracteres de redirection (sans le signe de output)
//-50:output avec d'autres caracteres de redirection (avec le signe de output)
//-5:output avec signe
//-1:error
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
void pipe_implementation(t_token **all, int number_exec);
int count_pipe(t_token **all);
t_list *get_all_builtins();
void state_command(t_token **token, int pipe, t_list *built, t_env *env);

//get_off_quote
int count_quote(char *command);
char *get_off_quote(char *old, int count);

//builtins utils
void take_all_quote(t_token **tok);
int checking_redir(t_token *temp);

//execve utils
char **get_all_path(t_env *env);


#endif