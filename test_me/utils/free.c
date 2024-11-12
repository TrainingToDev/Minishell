/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:08:29 by herandri          #+#    #+#             */
/*   Updated: 2024/11/12 04:44:59 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free for all minishell, but need attention for use
// first implementation

void free_string_array(char **array)
{
	int i = 0;

	if (!array)
		return;
	while (array[i])
		free(array[i++]);
	free(array);
}

void free_ast(t_ast *ast)
{
	if (!ast)
		return;
	if (ast->type == NODE_COMMAND)
		free_command(ast->command);
	else
	{
		free_ast(ast->left);
		free_ast(ast->right);
	}
	free(ast);
}

void free_command(t_command *cmd)
{
	if (!cmd)
		return;
	free_string_array(cmd->argv);
	free_redirections(cmd->redirs);
	free(cmd);
}

void free_redirections(t_redirection *redirs)
{
	t_redirection *tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		free(tmp->filename);
		free(tmp);
	}
}

void free_env_list(t_env_var *env_list)
{
	t_env_var *tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void free_tokens(t_token *tokens)
{
    t_token	*temp;

    while (tokens)
    {
        temp = tokens;
        tokens = tokens->next;
        if (temp->value)
            free(temp->value);
        free(temp);
    }
}
