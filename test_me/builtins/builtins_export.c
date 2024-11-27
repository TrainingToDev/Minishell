/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:42:29 by herandri          #+#    #+#             */
/*   Updated: 2024/11/17 11:39:22 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implementation ameliorate

int is_valid_id(const char *str)
{
	int i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// for only cmd export
void print_exported_vars(t_minishell *shell)
{
	t_env_var *current;

	current = shell->env_list;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		if (current->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}
// function need refactoring
int builtin_export(t_minishell *shell, char **args)
{
	int i;
	int status = 0;
	char *key;
	char *value;
	char *equal_sign;

	if (!args[1])
	{
		print_exported_vars(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			key = ft_substr(args[i], 0, equal_sign - args[i]);
			value = ft_strdup(equal_sign + 1);
		}
		else
		{
			key = ft_strdup(args[i]);
			value = NULL;
		}

		if (!is_valid_id(key))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
			free(key);
			free(value);
			i++;
			continue;
		}

		update_env(shell, key, value);
		free(key);
		free(value);
		i++;
	}
	return (status);
}


/* Analyse
export var = 

bash: export: `=': not a valid identifier
export testy

*/
/*
	valide syntax:
   -> export
   -> export var= 
   export var=       test
   
	
*/

// simple implementation
/* #define MAX_VAR_LENGTH 256
#define MAX_VAL_LENGTH 256


int parse_variable_assignment(const char *input, char *var, char *value)
{
	const char *equals_sign;
	size_t var_len;
	int i = 0;

	if (ft_strchr(input, ' '))
	{
		i++;
		return (-2);
	}
	if(i > 0)
		equals_sign = ft_strchr(input, '=');
	if (equals_sign == NULL)
	{
		printf("Error: Invalid format. Usage: export VAR=value\n");
		return (-1);
	}
	
	var_len = equals_sign - input;
	if (var_len >= MAX_VAR_LENGTH)
	{
		printf("Error: Variable name too long\n");
		return (-1);
	}
	ft_strlcpy(var, input, var_len);
	var[var_len] = '\0';

	ft_strlcpy(value, equals_sign + 1, MAX_VAL_LENGTH - 1);
	value[MAX_VAL_LENGTH - 1] = '\0';

	return (0);
}

void set_env_var(const char *var, const char *value) 
{
	if (setenv(var, value, 1) != 0)
		perror("Error setting environment var");
	else
		printf("Environment var set: %s=%s\n", var, value);
}

void export_variable(const char *input) 
{
	char var[MAX_VAR_LENGTH];
	char value[MAX_VAL_LENGTH];

	// Parse the input
	if (parse_variable_assignment(input, var, value) == 0)
		set_env_var(var, value);
} */


/* simple test in main
int main()
{
	char *input;

	while (1)
	{
		input = readline("Minishell> ");
		
		if (input == NULL || strlen(input) == 0)
		{
			free(input);
			continue;
		}

		add_history(input);

		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		if (strncmp(input, "export ", 7) == 0)
		{
			char *variable_assignment = input + 7;
			export_variable(variable_assignment);
		} 
		else
			printf("Command not found: %s\n", input);

		free(input);
	}

	return 0;
} */
