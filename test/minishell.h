/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:50:28 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/12 14:58:48 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_parse
{
    char *command;
    char **param;
    char    **input;
    char    **output;
    int pid;
}               t_parse;

typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
}               t_env;

void free_struct(t_parse *data);
void	add_new_env(t_env **lst, t_env *new);
int exact_command(char *data, char *command);
int is_alpha(int c);
int is_quote(char *string);
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

int get_number_of(char *input, int c);
char **input_file(char *input);
char **output_file(char *input);

#endif