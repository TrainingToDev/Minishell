/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:24:57 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/25 10:05:05 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_executable_path(char *path)
{
    struct stat path_stat;

    if (access(path, F_OK) != 0)
    {
        perror(path);
        return (127); // "No such file or directory"
    }
    if (stat(path, &path_stat) == -1)
    {
        perror(path);
        return (126); // Erreur d'accès au fichier
    }
    if (S_ISDIR(path_stat.st_mode))
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
        return (126); // Code d'erreur spécifique pour "Is a directory"
    }
    if (access(path, X_OK) != 0)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
        return (126); // Code d'erreur pour "Permission denied"
    }
    return (0); // Le chemin est valide pour exécution
}

static int prepare_extern_cmd(t_command *command, t_minishell *shell, char **path)
{
    int result;

	if (ft_strcmp(command->argv[0], ".") == 0)
    {
        ft_putstr_fd("minishell: .: command not found\n", STDERR_FILENO);
        return (127);
    }
    if (ft_strchr(command->argv[0], '/'))
    {
        result = check_executable_path(command->argv[0]);
        if (result != 0)
            return (result); // "Is a directory" or "Permission denied"  
        *path = ft_strdup(command->argv[0]);
        return (0);
    }
    *path = find_command_path(command->argv[0], shell->env_list);
    if (!(*path))
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(command->argv[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        return (127);
    }
    return (0);
}

static int process_extern(char *path, t_command *command, t_minishell *shell)
{
    pid_t	pid;

	pid = fork();
    if (pid == 0)
	{
        if (apply_redirections(command->redirs, shell) == -1)
		{
            perror("Error apply redir");
            exit(1);
        }
        execve(path, command->argv, convert_env_list(shell->env_list));
        perror("execve");
        exit(1);
    }
	else if (pid < 0)
	{
        perror("fork");
        return (1);
    }
    waitpid(pid, &shell->last_exit_status, 0);
    return (WEXITSTATUS(shell->last_exit_status));
}

int execute_extern_cmd(t_command *command, t_minishell *shell)
{
    char	*path;
    int		result;

	result = prepare_extern_cmd(command, shell, &path);
    if (result != 0)
        return result;

    result = process_extern(path, command, shell);
    free(path);
    return (result);
}