/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:24:34 by herandri          #+#    #+#             */
/*   Updated: 2024/11/02 11:10:57 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>


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


#endif