/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:21:30 by herandri          #+#    #+#             */
/*   Updated: 2025/01/29 00:40:55 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse(t_token *tokens, char *input)
{
	t_parser	parser;
	t_ast		*root;

	parser.current = tokens;
	root = parse_list(&parser, input);
	if (root && parser.current != NULL)
	{
		print_error(E_SYNTAX,  parser.current->next->value, ERR_SYN);
		free_ast(root);
		root = NULL;
	}
	return (root);
}
