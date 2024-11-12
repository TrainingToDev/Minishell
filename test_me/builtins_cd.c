/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:37:41 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:04:03 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implementation cd with struct

int builtin_cd(t_minishell *shell, char **args)
{
    char *dir;
    char *cwd;

    (void)shell;
    if (!args[1])
    {
        ft_putendl_fd("cd: missing argument", STDERR_FILENO);
        return (1);
    }
    if (args[2])
    {
        ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
        return (1);
    }
    dir = args[1];
    if (chdir(dir) != 0)
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        ft_putstr_fd(strerror(errno), STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putendl_fd(dir, STDERR_FILENO);
        return (1);
    }
    cwd = getcwd(NULL, 0);
    if (cwd)
    {
        update_env(shell, "PWD", cwd);
        free(cwd);
    }
    else
    {
        perror("cd");
        return (1);
    }
    return (0);
}


// test for cd
/* //use global variable for test
static char prev_dir[1024] = "";

// get_HOME
const char*	get_home_dir()
{
	const char	*home;

	home = getenv("HOME");
	if (home == NULL)
		printf("Error : HOME not define.\n");
	return (home);
}

// "cd -"
const char*	get_previous_directory()
{
	if (ft_strlen(prev_dir) == 0)
	{
		printf("Error: previous dir not define\n");
		return (NULL);
	}
	return (prev_dir);
}

// cd /////////
void	normalize_path(const char *path, char *normalized_path) 
{
	int j = 0;
	int in_slash_sequence = 0;
	int i = 0;
	while ( path[i] != '\0') 
	{
		if (path[i] == '/')
		{
			if (!in_slash_sequence)
			{
				normalized_path[j++] = path[i];
				in_slash_sequence = 1;
			}
		} 
		else 
		{
			normalized_path[j++] = path[i];
			in_slash_sequence = 0;
		}
		i++;
	}
	normalized_path[j] = '\0';
}

// main cd
void change_directory(const char *path)
{
	char current_dir[1024];
	char normalized_path[1024];
	
	// get cur rep
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("Error getcwd");
		return ;
	}
	if (path == NULL || ft_strcmp(path, "") == 0)
		path = get_home_dir();
	else if (ft_strcmp(path, "-") == 0)
		path = get_previous_directory();
	else if (ft_strcmp(path, "~") == 0)
		path = get_home_dir();
	else if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "./") == 0) 
	{
		printf("%s\n", current_dir);
		return ;
	}
	if (path == NULL)
		return ;
	normalize_path(path, normalized_path);
	path = normalized_path;
	// Change dir
	if (chdir(path) != 0)
		perror("Error cd");
	else 
	{
		ft_strlcpy(prev_dir, current_dir, sizeof(prev_dir));
		if (getcwd(current_dir, sizeof(current_dir)) != NULL)
			printf("%s\n", current_dir);
		else
			perror("Error getcwd");
	}
}
 */