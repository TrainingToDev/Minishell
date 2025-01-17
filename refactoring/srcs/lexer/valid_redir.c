#include "minishell.h"

int	valid_general_redir(t_token *token)
{
	if (!token->next)
	{
		print_error(E_SYNTAX, "newline", 2);
		return (0);
	}
	if (token->type == TOKEN_REDIRECT_OUT && token->next->type == TOKEN_PIPE)
	{
		print_error(E_SYNTAX, "|", 2);
		return (0);
	}
	if (token->next->type != TOKEN_WORD && token->next->type != TOKEN_PIPE)
	{
		print_error(E_SYNTAX, token->next->value, 2);
		return (0);
	}
	return (1);
}

int validate_force_overwrite(t_token *token)
{
	if (ft_strncmp(token->value, ">|", 2) == 0)
	{
		if (!token->next || token->next->type != TOKEN_WORD)
		{
			print_error(E_SYNTAX, "newline", 2);
			return (0);
		}
	}
	return (1);
}

int check_redirections(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_REDIRECT_OUT || tokens->type == TOKEN_APPEND
			|| tokens->type == TOKEN_REDIRECT_IN || tokens->type == TOKEN_HEREDOC)
		{
			if (!valid_general_redir(tokens))
				return (0);
			if (tokens->type == TOKEN_REDIRECT_OUT 
				&& !validate_force_overwrite(tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
