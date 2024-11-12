/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:24:53 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:47:08 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for test

void print_tokens(t_token *tokens)
{
    t_token *current = tokens;
    while (current)
    {
        printf("Token type: %d, value: '%s'\n", current->type, current->value);
        current = current->next;
    }
}

void print_env_list(t_env_var *env_list)
{
    t_env_var *current = env_list;
    while (current != NULL)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

void    display_error(const char *message)
{
	if (!message)
		return ;
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void display_syntax_error(const char *token)
{
    write(STDERR_FILENO, "Syntax error near unexpected token: ", 36);
    if (token)
        write(STDERR_FILENO, token, strlen(token));
    else
        write(STDERR_FILENO, "NULL", 4);
    write(STDERR_FILENO, "\n", 1);
}
