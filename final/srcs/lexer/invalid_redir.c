/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:47:39 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 01:18:38 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_unsup_simple_redir(const char *input)
{
	if (consecutive_redir_in(input))
		return (1);
	if (unsupported_redirs(input))
		return (1);
	return (0);
}

static int	is_unsup_output_redir(const char *input)
{
	if (isdigit(input[0]) && input[1] == '>')
	{
		if (input[2] == '&' && (isdigit(input[3]) || input[3] == '-'))
		{
			print_error(E_SUP, "Unsupported redirection", ERR_G);
			return (1);
		}
		if (input[2] == '&')
		{
			print_error(E_SUP, "Unsupported redirection", ERR_G);
			return (1);
		}
		print_error(E_SUP, "Unsupported redirection", ERR_G);
		return (TOKEN_UNKNOWN);
	}
	return (0);
}

static int	is_unsup_input_redir(const char *input)
{
	if (isdigit(input[0]) && input[1] == '<')
	{
		if (input[2] == '&' && (isdigit(input[3]) || input[3] == '-'))
		{
			print_error(E_SUP, "Unsupported redirection", ERR_G);
			return (1);
		}
		print_error(E_SUP, "Unsupported redirection", ERR_G);
		return (TOKEN_UNKNOWN);
	}
	if (input[0] == '<' && input[1] == '&' && isdigit(input[2]))
	{
		print_error(E_SUP, "Unsupported redirection", ERR_G);
		return (1);
	}
	return (0);
}

static int	is_unsup_descriptor_redir(const char *input)
{
	if (is_unsup_output_redir(input))
		return (1);
	if (is_unsup_input_redir(input))
		return (1);
	return (0);
}

t_token_type	invalid_redir(const char *input)
{
	if (is_unsup_simple_redir(input))
		return (TOKEN_UNKNOWN);
	if (is_unsup_descriptor_redir(input))
		return (TOKEN_UNKNOWN);
	return (TOKEN_WORD);
}
