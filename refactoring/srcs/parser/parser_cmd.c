/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:21:30 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 00:36:00 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**expand_argv(t_command *cmd, char *new_arg)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < cmd->argc)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	free(cmd->argv);
	new_argv[cmd->argc++] = new_arg;
	new_argv[cmd->argc] = NULL;
	return (new_argv);
}

static int	handle_word_token(t_parser *parser, t_command *cmd)
{
	char	*cleaned_value;
	char	**new_argv;

	cleaned_value = clean_quotes(parser->current->value);
	if (!cleaned_value)
	{
		print_error(E_NOMEM, "Memory allocation failed", ERR_SEGV);
		return (-1);
	}
	new_argv = expand_argv(cmd, cleaned_value);
	if (!new_argv)
	{
		print_error(E_NOMEM, "Memory allocation failed", ERR_SEGV);
		free(cleaned_value);
		return (-1);
	}
	cmd->argv = new_argv;
	parser_advance(parser);
	return (0);
}

static int	handle_redirection(t_parser *parser, t_command *cmd, char *input)
{
	t_redir	*redir;

	redir = parse_io_redirect(parser, input);
	if (!redir)
	{
		free(cmd->argv);
		return (-1);
	}
	redir->next = cmd->redirs;
	cmd->redirs = redir;
	return (0);
}

static int	process_token(t_parser *parser, t_command *cmd, char *input)
{
	if (is_token(parser, TOKEN_WORD))
	{
		if (handle_word_token(parser, cmd) == -1)
			return (-1);
	}
	else if (is_token(parser, TOKEN_REDIRECT_IN)
		|| is_token(parser, TOKEN_REDIRECT_OUT)
		|| is_token(parser, TOKEN_APPEND)
		|| is_token(parser, TOKEN_HEREDOC))
	{
		if (handle_redirection(parser, cmd, input) == -1)
			return (-1);
	}
	else
		return (1);
	return (0);
}

t_command	*parse_simple_cmd(t_parser *parser, char *input)
{
	t_command	*cmd;
	int			result;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	while (parser->current)
	{
		result = process_token(parser, cmd, input);
		if (result == -1)
		{
			free(cmd);
			return (NULL);
		}
		else if (result == 1)
			break ;
	}
	return (cmd);
}
