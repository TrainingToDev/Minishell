/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:42:13 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:07:03 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implementation with struct
int builtin_env(t_minishell *shell, char **args)
{
    t_env_var *current;

    if (args[1])
    {
        ft_putendl_fd("env: too many arguments", STDERR_FILENO);
        return (1);
    }

    current = shell->env_list;
    while (current)
    {
        // show only variable define
        if (current->value)
        {
            ft_putstr_fd(current->key, STDOUT_FILENO);
            ft_putchar_fd('=', STDOUT_FILENO);
            ft_putendl_fd(current->value, STDOUT_FILENO);
        }
        current = current->next;
    }
    return (0);
}


// mini test for simple implementation env
/* void print_env(char **envp)
{
    while (*envp) 
    {
        printf("%s\n", *envp);
        envp++;
    }
} */
