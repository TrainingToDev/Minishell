#include "minishell.h"

t_hdc	*get_heredoc_lines(const char *input, const char *delim)
{
	t_hdc	*content;
	char				**lines;

	if (!input || !delim)
		return (NULL);
	content = init_heredoc();
	if (!content)
		return (NULL);
	lines = split_lines(input);
	if (!lines)
	{
		free(content);
		return (NULL);
	}
	if (get_lines(content, lines, delim) == -1)
	{
		free_heredoc_content(content);
		free_split(lines);
		free(content);
		return (NULL);
	}
	free_split(lines);
	return (content);
}

