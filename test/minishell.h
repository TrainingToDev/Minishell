/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:50:28 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/18 14:30:15 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include "libft/libft.h"

typedef struct s_token
{
    char *token;
    int state;
    struct s_token *next;
}               t_token;

typedef struct s_parse
{
    char *command;
    char **param;
    char    **input;
    char    **output;
    int pid;
    struct s_parse *next;
}               t_parse;

typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
}               t_env;

void    free_struct(t_parse *data);
void	add_new_env(t_env **lst, t_env *new);
int exact_command(char *data, char *command);
int is_alpha(int c);
int is_variable(char *string);
int list_size(t_env *env);
int check_pipe(char *input);
t_parse  *get_struct(char *input);
t_parse **get_data(char *input, int len);
t_env	*get_env(char **env);
t_env	*new_env(char *env);
t_env *local_variable(void);
//char	*get_string(char *env, int i, int len, int c);

//builtins

int    echo_command(t_parse *data);
int add_new_var(t_parse *data, t_env *var);
int echo_without_option(t_parse *data);
int pwd_command(t_parse *data);
int env_command(t_env *env, t_parse *data);
int export_command(t_env *env, t_parse *data);

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
char **input_file(char *input);
char **output_file(char *input);

//get_token
char **tokening(char *input);
void    add_new_token(t_token **tok, t_token *new);
t_token *g_token(char *token);
t_token **get_all_token(char **data, int len);
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
//-2:fichier de redirection avec le signe de redirection
//3:eof de heredoc sans signe de heredoc 
//-3:eof de heredoc avec signe de heredoc
//4:input sans signe
//-4:input avec signe
//-1:error
void    get_all_state(t_token **all);
void command (t_token **tok);
void  is_redir(t_token **tok);
void    is_heredoc(t_token **tok);
void    is_input_file(t_token **tok);

#endif