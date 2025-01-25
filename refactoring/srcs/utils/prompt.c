#include "minishell.h"

int	check_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd(COLOR_RED"Error: "COLOR_RESET, 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" does not accept any arguments.\n", 2);
		ft_putstr_fd("Usage: ", 2);
		ft_putendl_fd(argv[0], 2);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
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

char    *prompt_input(char *prompt)
{
	char    *input;

	input = NULL;
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	if (!input)
	{
		write(1, "exit\n", 5);
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}
