#include "minishell.h"

static void    free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
	{
		printf("LOG: Freeing token value: %s\n", token->value);
		free(token->value);
	}
	free(token);
}

void	free_token_list(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		printf("LOG: Freeing token with value: %s\n", tokens->value);
		
		free_token(tokens);
		tokens = tmp;
		printf("LOG: All tokens freed.\n");
	}
}

