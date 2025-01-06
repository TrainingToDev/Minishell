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
