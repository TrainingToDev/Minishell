#include "minishell.h"





static char	**dup_lines(t_hdc *content, const char *line)
{
	char	**new_lines;
	size_t	j;

	new_lines = malloc(sizeof(char *) * (content->count + 1));
	if (!new_lines)
		return (NULL);
	j = 0;
	while (j < content->count)
	{
		new_lines[j] = content->lines[j];
		j++;
	}
	free(content->lines);
	new_lines[content->count] = ft_strdup(line);
	if (!new_lines[content->count])
	{
		while (j-- > 0)
			free(new_lines[j]);
		free(new_lines);
		return (NULL);
	}
	return (new_lines);
}

int	add_line(t_hdc *content, const char *line)
{
	char	**new_lines;

	new_lines = dup_lines(content, line);
	if (!new_lines)
		return (-1);

	content->lines = new_lines;
	content->count++;
	return (0);
}
