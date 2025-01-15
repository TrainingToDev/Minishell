/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:04:20 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 11:34:22 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd_command(t_token **tok)
{
	t_token *token;

	token = *tok;
	if (checking_redir(token) == 1)
		printf("need redirection function");//redirection function
	while (token)
	{
		if (is_option(token->token) == 1 && token->state == 6)
		{
			write (2,"No option is tolerated\n", 23); // update
            return (2);////$? = 2 when the option don ' t exist
		}
		token = token->next;
	}
	printf("%s\n", getcwd(NULL, 0));
	return (0);//valeur de retour $?
}