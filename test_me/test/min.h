#ifndef MIN_H
# define MIN_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <ctype.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>
# include <limits.h>

# define COLOR_RESET "\033[0m"
# define COLOR_GREEN "\033[32m"
# define COLOR_BLUE  "\033[34m"
# define COLOR_RED   "\033[31m"


#define STATUS_READ 0
#define STATUS_WRITE 1


// extern volatile sig_atomic_t g_signal_received;

typedef enum e_token_type // ok
{
	TOKEN_WORD, // (cmd, args)      //0
	TOKEN_PIPE, // |                //1
	TOKEN_REDIRECT_IN, // <         //2
	TOKEN_REDIRECT_OUT, // >        //3
	TOKEN_APPEND, // >>             //4
	TOKEN_HEREDOC, // <<            //5
	TOKEN_AND, // &&                //6
	TOKEN_OR, // ||                 //7
	TOKEN_LPAREN, // '('            //8
	TOKEN_RPAREN, // ')'            //9
	TOKEN_UNKNOWN, // not define    //11
}   t_token_type;

typedef struct s_token //ok
{
	char            *value;
	t_token_type    type;
	int             expand;
	struct s_token  *next;
}   t_token;

typedef struct s_heredoc_content
{
	char	**lines; //tab line
	size_t	count; //nbr line
}			t_heredoc_content;

typedef enum e_redir_type //ok
{
	REDIR_IN,        // '<'   //0
	REDIR_OUT,       // '>'   //1
	REDIR_APPEND,    // '>>'  //2
	REDIR_HEREDOC    // '<<'  //3
}   t_redir_type;

typedef struct s_redirection //ok
{
	t_redir_type             type;
	char                     *filename;
	struct s_redirection     *next;
}   t_redirection;

typedef enum e_node_type //ok
{
	NODE_COMMAND, // cmd 
	NODE_PIPE, // |
	NODE_AND,  // &&
	NODE_OR,  // ||
	NODE_LOGICAL, // manage logical for cmd
	NODE_SUBSHELL // manage ()
}   t_node_type;

typedef struct s_ast //ok
{
	t_node_type       type;
	struct s_command  *command;
	t_token_type      operator; // and | or
	struct s_ast      *left;
	struct s_ast      *right;
}   t_ast;


typedef struct s_command //ok
{
	char                **argv; // argument
	int                 argc;   // nb srg
	t_redirection       *redirs;  //redir ass
}   t_command;

typedef struct s_env_var //ok
{
	char                *key;
	char                *value;
	struct s_env_var    *next;
}   t_env_var;

typedef struct s_minishell //ok
{
	t_env_var   *env_list;
	int         last_exit_status; //$?
	int         interactive;
	int         original_stdin;
    int         original_stdout;
    int         original_stderr;
}   t_minishell;



enum	e_mini_error
{
	E_QUOTE = 1,          // syntax Unclosed quote
	E_NODIR = 2,          // Aucun répertoire trouvé
	E_PDENIED = 3,         // Permission refusée
	E_NOCMD = 6,          // Command not found
	E_DUPFD = 7,          // dupplication fd failed
	E_FORK = 8,           // fork failed
	E_PIPE = 9,           // pipe failed
	E_SYNTAX = 10,       // syntax error near unexpected token
	E_NOMEM = 11,         // Erreur d'allocation mémoire
	E_ISDIR = 12,         // Fichier spécifié est un répertoire
	E_NOTDIR = 13         // Not a directory
};





#endif



