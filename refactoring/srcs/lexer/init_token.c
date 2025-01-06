#include "minishell.h"

t_token	*create_token(t_token_type type, const char *value, int expand)
{
	t_token	*new_token;

	if (!value)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		print_error(E_NOMEM,"Memory allocation error", 2);
		return (NULL);
	}
	new_token->type = type;
	new_token->expand = expand;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return ;
	if (new_token->next)
	{
		printf("Token already linked\n"); //need amel
		return ;
	}
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void add_word_token(t_token **tokens, char *input, size_t *i)
{
	char		*value;
	t_token		*new_token;
	int			expand;

	if (!tokens)
		return ;
	expand = 0;
	value = extract_word_value(input, i, &expand);
	if (!value)
	{
		free_token_list(*tokens);
		*tokens = NULL;
		return ;
	}
	new_token = create_token(TOKEN_WORD, value, expand);
	free(value);
	if (!new_token)
	{
		free_token_list(*tokens);
		*tokens = NULL;
		return ;
	}
	add_token(tokens, new_token);
}
