/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:50:28 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 12:26:50 by miaandri         ###   ########.fr       */
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
    char *option;
    char *param;
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
t_parse  *get_struct(char *input);
t_env	*get_env(char **env);
t_env *last_env(t_env *env);
int    echo_command(t_parse *data);
int echo_without_option(t_parse *data);
int pwd_command(t_parse *data);
int env_command(t_env *env, t_parse *data);
int export_command(t_env *env, t_parse *data);
char	*get_string(char *env, int i, int len, int c);

#endif