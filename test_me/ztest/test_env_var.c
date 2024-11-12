/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:58:43 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:56:40 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_env_var
{
	char                *key;
	char                *value;
	struct s_env_var    *next;
}   t_env_var;


void print_env_list(t_env_var *env_list)
{
	t_env_var	*current;

	current = env_list;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void free_env_list(t_env_var *env_list)
{
	t_env_var	*current;
	t_env_var	*next;

	current = env_list;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

// Function to assign key and value to env_var
int	assign_key_value(t_env_var *env_var, const char *input_env)
{
    char	*sep;

    sep = ft_strchr(input_env, '=');
    if (sep)
    {
        env_var->key = ft_substr(input_env, 0, sep - input_env);
        if (!env_var->key)
            return (-1);
        env_var->value = ft_strdup(sep + 1);
        if (!env_var->value)
            return (-1);
    }
    else
    {
        env_var->key = ft_strdup(input_env);
        if (!env_var->key)
            return (-1);
        env_var->value = ft_strdup("");
        if (!env_var->value)
            return (-1);
    }
    return (0);
}

void	free_env_var(t_env_var *env_var)
{
    if (env_var)
    {
        free(env_var->key);
        free(env_var->value);
        free(env_var);
    }
}

// Function to create a t_env_var structure from a "KEY=VALUE" string
t_env_var	*create_env_var(const char *input_env)
{
    t_env_var	*env_var;

    env_var = malloc(sizeof(t_env_var));
    if (!env_var)
        return (NULL);
    if (assign_key_value(env_var, input_env) == -1)
    {
        free_env_var(env_var);
        return (NULL);
    }
    env_var->next = NULL;
    return (env_var);
}

// Function to add an element to the end of the list
void add_env_var(t_env_var **env_list, t_env_var *new_var)
{
	t_env_var	*current;

	if (!env_list || !new_var)
		return ;
	new_var->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = new_var;
	}
	else
	{
		current = *env_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_var;
	}
}

t_env_var *convert_envp_to_list(char **envp)
{
    t_env_var   *env_list;
    t_env_var   *new_var;
    int         i;

	env_list = NULL;
	i = 0;
    while (envp[i])
    {
        new_var = create_env_var(envp[i]);
        if (!new_var)
        {
            free_env_list(env_list);
            return (NULL);
        }
		add_env_var(&env_list, new_var);
        i++;
    }
    return (env_list);
}

// gcc -Wall -Wextra -Werror test_env_var.c ../libft/libft.a
int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	t_env_var *env_list = convert_envp_to_list(envp);
	if (!env_list)
	{
		fprintf(stderr, "Error for creation list envp.\n");
		return (EXIT_FAILURE);
	}
	print_env_list(env_list);
	free_env_list(env_list);

	return (EXIT_SUCCESS);
}
