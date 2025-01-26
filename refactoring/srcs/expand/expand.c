#include "minishell.h"

static char *append_char_to_result(char *result, char c)
{
    char	*temp;

	temp = ft_strjoin_char(result, c);
	free(result);
	return (temp);
}

static char	*process_normal_char(const char *src, size_t *i, char *result)
{
	result = append_char_to_result(result, src[*i]);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}

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

char *expand_variables_in_str(const char *src, t_minishell *shell)
{
    size_t	i;
    char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
		{
			result = process_dollar(src, &i, result, shell);
			if (!result)
				return (NULL);
		}
		else
		{
			result = process_normal_char(src, &i, result);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}







