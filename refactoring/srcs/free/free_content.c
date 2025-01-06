#include "minishell.h"

void free_split(char **split)
{
	size_t i;

	if (!split)
		return;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void free_heredoc_content(t_hdc *content)
{
	size_t	i;

	if (!content || !content->lines)
		return ;
	i = 0;
	while (i < content->count)
	{
		free(content->lines[i]);
		i++;
	}
	free(content->lines);
	content->lines = NULL;
	content->count = 0;
}

