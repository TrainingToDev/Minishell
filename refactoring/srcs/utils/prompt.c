#include "minishell.h"

char	*format_prompt(void)
{
	char	*cwd;
	char	*prompt;
	char	*path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("minishell");
	if (!cwd)
		return (NULL);
	path = ft_strjoin("\001" COLOR_BLUE "\002", cwd);
	free(cwd);
	if (!path)
		return (NULL);
	prompt = ft_strjoin("\001" COLOR_GREEN "\002minishell:", path);
	free(path);
	if (!prompt)
		return (NULL);
	path = prompt;
	prompt = ft_strjoin(prompt, "\001" COLOR_RESET "\002$ ");
	free(path);
	if (!prompt)
		return (NULL);
	return (prompt);
}
