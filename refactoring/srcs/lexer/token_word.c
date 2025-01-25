#include "minishell.h"

void add_word_token(t_token **tokens, char *input, size_t *i)
{
	char	*value;
	t_token	*new_token;
	int		expand;

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
