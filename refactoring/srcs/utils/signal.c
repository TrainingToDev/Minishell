#include "minishell.h"

int	status_manager(int new_status, int mode)
{
	static int	status;

	status = 0;
	if (mode == STATUS_READ) //read
		return status;
	else if (mode == STATUS_WRITE) // write
		status = new_status;
	return (status);
}

static void	manage_signal(int sig)
{
	if (sig == SIGINT) //CTRL+C
	{
		status_manager(SIGINT, STATUS_WRITE);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, manage_signal);
	signal(SIGQUIT, SIG_IGN);
}

