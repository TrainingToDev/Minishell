#include "minishell.h"

void	print_heredoc_content(const t_hdc *content)
{
	size_t	i;

	if (!content)
	{
		printf("No heredoc content to display.\n");
		return ;
	}
	if (!content->lines || content->count == 0)
	{
		printf("Heredoc content is empty.\n");
		return ;
	}
	printf("Heredoc content (%zu lines):\n", content->count);
	i = 0;
	while (i < content->count)
	{
		printf("Line %zu: %s\n", i + 1, content->lines[i]);
		i++;
	}
}

void	process_heredoc(const t_token *tokens, const char *input)
{
	const t_token		*current;
	t_hdc				*content;
	char				*delimiter;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (current->next)
				delimiter = current->next->value;
			else
				delimiter = NULL;
			if (delimiter)
			{
				printf("Handling heredoc with delimiter: %s\n", delimiter);
				content = get_heredoc_lines(input, delimiter);
				if (content)
				{
					print_heredoc_content(content);
					free_heredoc_content(content);
					free(content);
				}
			}
		}
		current = current->next;
	}
}

const char	*get_token_type_name(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("TOKEN_WORD");
	else if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	else if (type == TOKEN_APPEND)
		return ("TOKEN_APPEND");
	else if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	else if (type == TOKEN_AND)
		return ("TOKEN_AND");
	else if (type == TOKEN_OR)
		return ("TOKEN_OR");
	else if (type == TOKEN_LPAREN)
		return ("TOKEN_LPAREN");
	else if (type == TOKEN_RPAREN)
		return ("TOKEN_RPAREN");
	else if (type == TOKEN_UNKNOWN)
		return ("TOKEN_UNKNOWN");
	else
		return ("UNKNOWN_TYPE");
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token Type: %s, Value: [",
			   get_token_type_name(current->type));
		if (current->value)
			printf("%s", current->value);
		else
			printf("NULL");
		printf("], Expand: %d\n", current->expand);
		current = current->next;
	}
}
