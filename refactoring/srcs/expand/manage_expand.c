#include "minishell.h"

static int expand_single_token(t_token *token, t_token *tokens, t_minishell *shell)
{
	char	*expanded;

	if (token->type == TOKEN_WORD)
	{
		if (token->expand == 1 || (strchr(token->value, '$') 
			&& !is_single_quoted(token->value)))
		{
			expanded = expand_variables_in_str(token->value, shell);
			if (!expanded)
			{
				fprintf(stderr, "Error: Memory allocation failed during variable expansion.\n");
				free_token_list(tokens);
				shell->running = 0;
				return (0);  // Erreur => on arrête
			}
			free(token->value);
			token->value = expanded;
		}
	}
	return (1);
}

void expand_token_list(t_token *tokens, t_minishell *shell)
{
	t_token *current = tokens;

	while (current)
	{
		if (!expand_single_token(current, tokens, shell))
			return ;
		current = current->next;
    }
}
