/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:24:34 by herandri          #+#    #+#             */
/*   Updated: 2024/11/02 12:17:39 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define RUN 1
# define CMD_NOT_FOUND 127


typedef struct s_data_path
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;
}			t_data_path;

typedef struct s_cmd_list
{
	char *data;
	int type;
}		cmd_list;

char	*get_command_path(char *cmd, char **envp);
void	free_split(char **split);
void	ft_error(const char *message, int exit_code);
void 	exit_cmd(char *input);
void	print_error_message(char *shell, int errnum, char *filename);
#endif