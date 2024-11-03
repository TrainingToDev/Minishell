/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:42:29 by herandri          #+#    #+#             */
/*   Updated: 2024/11/03 12:04:13 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
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

#define MAX_VAR_LENGTH 256
#define MAX_VAL_LENGTH 256


int parse_variable_assignment(const char *input, char *var, char *value)
{
    const char *equals_sign;
    size_t var_len;

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
}


/* 
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
