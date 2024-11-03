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

void	ft_free(char **dest);
int exact_command(char *data, char *command);
int is_alpha(int c);
t_parse  *get_struct(char *input);
int    echo_command(t_parse *data);
int echo_without_option(t_parse *data);
int pwd_command(t_parse *data);

#endif