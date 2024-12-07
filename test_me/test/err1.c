
#include "min.h"




enum	e_mini_error
{
	ERR_QUOTE = 1,          // syntax Unclosed quote
	ERR_NODIR = 2,          // Aucun répertoire trouvé
	ERR_PDENIED = 3,         // Permission refusée
	ERR_NOCMD = 6,          // Command not found
	ERR_DUPFD = 7,          // dupplication fd failed
	ERR_FORK = 8,           // fork failed
	ERR_PIPE = 9,           // pipe failed
	ERR_SYNTAX = 10,       // syntax error near unexpected token
	ERR_NOMEM = 11,         // Erreur d'allocation mémoire
	ERR_ISDIR = 12,         // Fichier spécifié est un répertoire
	ERR_NOTDIR = 13         // Not a directory
};



// signal
// Mode: read, write

int	status_manager(int new_status, int mode)
{
	static int	status;

	status = 0;
	if (mode == STATUS_READ) //read
		return status;
	else if (mode == STATUS_WRITE) // write
		status = new_status;
	return status;
}

//error message
char	*get_error_message(int err_type)
{
	if (err_type == ERR_QUOTE)
		return ("minishell: syntax Unclosed quote\n");
	else if (err_type == ERR_NODIR)
		return ("minishell: No such file or directory: ");
	else if (err_type == ERR_PDENIED)
		return ("minishell: Permission denied: ");
	else if (err_type == ERR_NOCMD)
		return ("minishell: Command not found: ");
	else if (err_type == ERR_DUPFD)
		return ("minishell: dup2 failed\n");
	else if (err_type == ERR_FORK)
		return ("minishell: fork failed\n");
	else if (err_type == ERR_PIPE)
		return ("minishell: pipe failed\n");
	else if (err_type == ERR_SYNTAX)
		return ("minishell: syntax error near unexpected token `");
	else if (err_type == ERR_NOMEM)
		return ("minishell: allocation failed: Cannot allocate memory\n");
	else if (err_type == ERR_ISDIR)
		return ("minishell: Is a directory: ");
	else if (err_type == ERR_NOTDIR)
		return ("minishell: Not a directory: ");
	return (NULL);
}

void	*print_error(int err_type, char *param, int err)
{
	char *error_message;

	status_manager(err, STATUS_WRITE); // update status
	error_message = get_error_message(err_type); //get msg for type

	if (!error_message)
	{
		ft_putstr_fd("minishell: error Unknown\n", 2);
		return (NULL);
	}
	ft_putstr_fd(error_message, 2); // print error msg

	
    if (err_type == ERR_SYNTAX && param)
    {
        ft_putstr_fd(param, 2); // Append problematic token
        ft_putstr_fd("'\n", 2); // Add closing quote
        return (NULL);
    }

	if (param) // print param if ok, for DIR
		ft_putendl_fd(param, 2);
	return (NULL);
}
//************************* */
// =00000000000000000+++++++++++++++++++++++++++++++





// Gestion des signaux
void	signal_handl(int sig)
{
	if (sig == SIGINT) //CTRL+C
	{
		status_manager(SIGINT, STATUS_WRITE); // save signal received
		ft_putstr_fd("\n", 1); // Add new ligne prompt
		rl_on_new_line(); // Prepare readline for new prompt
		rl_replace_line("", 0); //Clear current line
		rl_redisplay(); // Redisplay prompt
	}
}

void	setup_signal(void)
{
	signal(SIGINT, signal_handl); //CTRL+C
	signal(SIGQUIT, SIG_IGN); // ctrl+'\'
}