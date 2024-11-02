/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:53:04 by herandri          #+#    #+#             */
/*   Updated: 2024/11/02 12:41:41 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test only for cmd
// compile with: 
// gcc main.c builtins_cd.c builtins_exit.c utils.c libft/libft.a -lreadline

int main(int argc, char **argv, char **envp) 
{
	char	*input;
	char	*path;
	char	*cmd_path;
	int		status;
	pid_t 	pid;

	while (RUN)
	{
		input = readline("Minishell> ");
		
		if (input == NULL || ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		if (ft_strncmp(input, "cd", 2) == 0)
		{
			path = NULL;
			if (ft_strlen(input) > 3)
				path = input + 3;
			change_directory(path);
		}
		else
		{
			cmd_path = get_command_path(input, envp);
            if (cmd_path)
            {
				pid = fork();
                if (pid == 0)
                {
                    execve(cmd_path, argv, envp);
                    perror("Execution failed"); 
                    exit(EXIT_FAILURE);
                }
                else if (pid > 0)
                    waitpid(pid, &status, 0); 
                free(cmd_path);
            }
            else
                printf("Commande not found: %s\n", input);
        }
		free(input);
	}
	return (0);
}
