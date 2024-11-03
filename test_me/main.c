/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:53:04 by herandri          #+#    #+#             */
/*   Updated: 2024/11/03 17:23:55 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test only for cmd
// compile with: 
// gcc main.c builtins_cd.c builtins_exit.c utils.c libft/libft.a -lreadline


// key_enter = \n 
// $ = ls
// export var=var_name
/* 
	minishell: name_cmd: -c: invalid option
	name_cmd: usage: pwd
	// sudo
	Minishell: /usr/bin/sudo: Permission denied
	ls <>: Minishell: syntax error near unexpected token `newline'

 */

/*
	echo [-n] [arg …]
	cd [directory] or cd -
	exit [n]
	export name[=value]...
	pwd
	unset [name]
	env

*/
// cmd in "cmd"
// error tapping cmd


// resolve segfault with CTRL-D

// prompt print :
/* 
	Minishell:~$

*/

/* 

	Grammar symbols and quoting

	DLESS : <<
	DGREAT : >>
	AND_IF: &&
	OR_IF: ||
	RLESS: <
	RGREAT: >
	PIPE: |
	QDBL: ""
	QSMP: ''
	other: * ? [] # ~ = %
	AMP: &
	
	
 */


//pipe and input/output Redirection
// a | b | c | d > outfile < infile







// tcsetattr(), tcgetattr(), tgetent()|tgetflag(), tgetnum(), tgetstr

int main(int argc, char **argv, char **envp) 
{
	char	*input;
	char	*path;
	char	*cmd_path;
	int		status;
	pid_t 	pid;
	// char	*data_cmd;
	// int		i;

	while (RUN)
	{
		input = readline("Minishell> ");
		// while(input[i])
        // {
        //     if(input[i] != '\0')
        //         data_cmd[i] = input[i];
        //     i++; 
        // }
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
            printf("input cmd: %s\n", &cmd_path[0]);
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
