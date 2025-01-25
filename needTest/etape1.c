/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etape1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:21:30 by herandri          #+#    #+#             */
/*   Updated: 2025/01/25 14:05:58 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "min.h"

// Gestion de l'argument du programme   ok
int	check_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd(COLOR_RED"Error: "COLOR_RESET, 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" does not accept any arguments.\n", 2);
		ft_putstr_fd("Usage: ", 2);
		ft_putendl_fd(argv[0], 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
// Gestion de prompt  ok

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


// free token
void    free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	free(token);
	token = NULL;
}

void	free_token_list(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free_token(tokens);
		tokens = tmp;
	}
}


// signal
// Mode: read, write  ok

int	status_manager(int new_status, int mode)
{
	static int	status = 0;

	if (mode == STATUS_READ) //read
		return status;
	else if (mode == STATUS_WRITE) // write
		status = new_status;
	return (status);
}

//error message  ok
char *get_error_msg(int err_type)
{
	// Syntax errors
	if (err_type == E_QUOTE)
		return ("minishell: syntax Unclosed quote\n");
	else if (err_type == E_SYNTAX)
		return ("minishell: syntax error near unexpected token `");

	// File or directory errors
	else if (err_type == E_NODIR)
		return ("minishell: No such file or directory: ");
	else if (err_type == E_ISDIR)
		return ("minishell: Is a directory: ");
	else if (err_type == E_NOTDIR)
		return ("minishell: Not a directory: ");
	else if (err_type == E_PDENIED)
		return ("minishell: Permission denied: ");

	// Command errors
	else if (err_type == E_NOCMD)
		return ("minishell: Command not found: ");
	else if (err_type == E_DUPFD)
		return ("minishell: dup2 failed\n");
	else if (err_type == E_FORK)
		return ("minishell: fork failed\n");
	else if (err_type == E_PIPE)
		return ("minishell: pipe failed\n");

	// Memory errors
	else if (err_type == E_NOMEM)
		return ("minishell: Cannot allocate memory\n");

	// unknown errors
	return (NULL);
}


//ok
void	*print_error(int err_type, char *param, int err)
{
	char *error_message;

	status_manager(err, STATUS_WRITE); // update status
	error_message = get_error_msg(err_type); //get msg for type

	if (!error_message)
	{
		ft_putstr_fd("minishell: error Unknown\n", 2);
		return (NULL);
	}
	ft_putstr_fd(error_message, 2); // print error msg

	 // errors de syntaxe
	if (err_type == E_SYNTAX && param)
	{
		ft_putstr_fd(param, 2);
		ft_putstr_fd("'\n", 2); 
		return (NULL);
	}

	if (param) // print param if ok, for DIR
		ft_putendl_fd(param, 2);
	return (NULL);
}
//************************* */
// =00000000000000000+++++++++++++++++++++++++++++++





// Gestion des signaux ok

// configuration
static void	setup_signal(int signum, void (*signal_handler)(int))
{
	struct sigaction	action;

	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(signum, &action, NULL);
}


//parents
void	reset_prompt(int sig)
{
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	status_manager(128 + sig, STATUS_WRITE);
}


void	main_signals(void)
{
	setup_signal(SIGINT, reset_prompt); // `Ctrl+C`
	setup_signal(SIGQUIT, SIG_IGN); // `Ctrl+\`
}

// enfants
void	child_signal(int sig)
{
	if (sig == SIGINT)
		ft_putendl_fd("", STDOUT_FILENO);
	else if (sig == SIGQUIT)
		ft_putendl_fd("Quit", STDOUT_FILENO); 
}

void	manage_child(void)
{
	setup_signal(SIGINT, child_signal); // `Ctrl+C`
	setup_signal(SIGQUIT, child_signal); // `Ctrl+\`
}

//heredocs
void	heredoc_signal(int sig)
{
	(void) sig;
	ft_putendl_fd("", STDOUT_FILENO);
	ft_putendl_fd("^C", STDOUT_FILENO);
	status_manager(130, STATUS_WRITE);
	exit(130);
}
//begin
void	manage_heredoc(void)
{
	setup_signal(SIGINT, heredoc_signal); // `Ctrl+C`
	setup_signal(SIGQUIT, SIG_IGN); // `Ctrl+\`
}

//ctrl+C heredoc
void	main_heredoc(void)
{
	setup_signal(SIGINT, SIG_IGN);
	setup_signal(SIGQUIT, SIG_IGN);
}










// void	handle_eof(void)
// {
// 	ft_putstr_fd("Exiting minishell. Goodbye!\n", 1);
// 	exit(EXIT_SUCCESS);
// }



// void    display_error(const char *message)
// {
// 	if (!message)
// 		return ;
// 	write(STDERR_FILENO, "Error: ", 7);
// 	write(STDERR_FILENO, message, strlen(message));
// 	write(STDERR_FILENO, "\n", 1);
// }


// environment utils

void print_env_list(t_env_var *env_list) //ok
{
	t_env_var	*current;

	current = env_list;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void free_env_list(t_env_var *env_list) //ok
{
	t_env_var	*current;
	t_env_var	*next;

	current = env_list;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}



//environnement

int	assign_key_value(t_env_var *env_var, const char *input_env) //ok
{
    char	*sep;

    sep = ft_strchr(input_env, '=');
    if (sep)
    {
        env_var->key = ft_substr(input_env, 0, sep - input_env);
        if (!env_var->key)
            return (-1);
        env_var->value = ft_strdup(sep + 1);
        if (!env_var->value)
            return (-1);
    }
    else
    {
        env_var->key = ft_strdup(input_env);
        if (!env_var->key)
            return (-1);
        env_var->value = ft_strdup("");
        if (!env_var->value)
            return (-1);
    }
    return (0);
}

void	free_env_var(t_env_var *env_var) //ok
{
    if (env_var)
    {
        free(env_var->key);
        free(env_var->value);
        free(env_var);
    }
}

t_env_var	*create_env_var(const char *input_env) //ok
{
    t_env_var	*env_var;

    env_var = malloc(sizeof(t_env_var));
    if (!env_var)
        return (NULL);
    if (assign_key_value(env_var, input_env) == -1)
    {
        free_env_var(env_var);
        return (NULL);
    }
    env_var->next = NULL;
    return (env_var);
}

// add_back
void add_env_var(t_env_var **env_list, t_env_var *new_var) //ok
{
	t_env_var	*current;

	if (!env_list || !new_var)
		return ;
	new_var->next = NULL;
	if (*env_list == NULL)
		*env_list = new_var;
	else
	{
		current = *env_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_var;
	}
}

t_env_var *convert_envp_to_list(char **envp) //ok
{
    t_env_var   *env_list;
    t_env_var   *new_var;
    int         i;

	env_list = NULL;
	i = 0;
    while (envp[i])
    {
        new_var = create_env_var(envp[i]);
        if (!new_var)
        {
            free_env_list(env_list);
            return (NULL);
        }
		add_env_var(&env_list, new_var);
        i++;
    }
    return (env_list);
}




// lexer




t_token *create_token(t_token_type type, const char *value, int expand) //ok
{
	t_token *new_token;

	if (!value)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		print_error(E_NOMEM, "Memory allocation error", 11);
		return (NULL);
	}
	new_token->type = type;
	new_token->expand = expand;
	new_token->next = NULL;
	return (new_token);
}


void	add_token(t_token **tokens, t_token *new_token) //ok
{
	t_token	*current;

	if (!tokens || !new_token)
	{
		return ;
	}
		
	if (new_token->next)
	{
		printf("Token already linked");
		return ;
	}
	if (!*tokens)
	{
		*tokens = new_token;
		// printf("LOG: new_token added as the first token in the list!!!\n");
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
	
	// printf("LOG: new_token added to the end of the list at %p\n", (void *)current->next);
	
}


int	is_quote(char c) //ok
{
	return (c == '\'' || c == '\"');
}

int	ft_isspace(int c) //libft ok
{
	return ((c >= 9 && c <= 13) || c == ' ');
}



t_token_type get_op_token(const char *op) //ok
{
	if (ft_strncmp(op, ">|", 2) == 0)
		return (TOKEN_REDIRECT_OUT); // Ajoute le type pour `>|`
	else if (ft_strncmp(op, "&&", 2) == 0)
		return (TOKEN_AND);
	else if (ft_strncmp(op, "||", 2) == 0)
		return (TOKEN_OR);
	else if (ft_strncmp(op, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp(op, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (*op == '>')
		return (TOKEN_REDIRECT_OUT);
	else if (*op == '<')
		return (TOKEN_REDIRECT_IN);
	else if (*op == '|')
		return (TOKEN_PIPE);
	else if (*op == '(')
		return (TOKEN_LPAREN);
	else if (*op == ')')
		return (TOKEN_RPAREN);
	else
		return (TOKEN_UNKNOWN); // Cas d'erreur
}

//utils
int	is_operator(const char *str) //ok
{
	static const char	*double_operators[] = { 
		"&&", "||", ">>", "<<", ">|", NULL
	};
	static const char	single_operators[] = "|><()";
	int					i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	while (double_operators[i])
	{
		if (ft_strncmp(str, double_operators[i], 2) == 0)
			return (2);
		i++;
	}
	if (ft_strchr(single_operators, *str))
		return (1);
	return (0);
}

//* manage operator */ ok

static char *extract_operator_value(char *input, size_t *i, int *op_len)
{
	if (!input || !i || !op_len)
		return (NULL);
	*op_len = is_operator(&input[*i]);
	if (*op_len == 0)
	{
		print_error(E_SYNTAX, &input[*i], 10);
		return (NULL);

	}
	return ft_substr(input, *i, *op_len);
}

void add_operator_token(t_token **tokens, char *input, size_t *i)
{
	int     op_len;
	char    *value;
	t_token *new_token;

	value = extract_operator_value(input, i, &op_len);
	if (!value)
		return ;
	new_token = create_token(get_op_token(&input[*i]), value, 0);
	free(value);
	if (!new_token)
		return ; //msg
	add_token(tokens, new_token);
	*i += op_len;
}
//**** */




//manage quote //ok
char *extract_quoted_value(char *input, size_t *i, int *expand)
{
	size_t	start;
	char	*value;

	if (!input || !i || !expand)
		return (NULL);
	*expand = (input[*i] == '\"');
	start = (*i)++;
	while (input[*i] && input[*i] != input[start])
		(*i)++;
	if (!input[*i])
	{
		print_error(E_QUOTE, NULL, 1);
		return (NULL);
	}
	value = ft_substr(input, start, (*i) - start + 1);
	if (!value)
		return (NULL);
	(*i)++;
	return (value);
}



/******* */
char	*join_and_free(char *value, char *part) //ok
{
	char	*tmp;

	tmp = ft_strjoin(value, part);
	free(value);
	free(part);
	if (!tmp)
		print_error(E_NOMEM, NULL, 11);
	return (tmp);
}

char	*extract_part(char *input, size_t *i) //ok
{
	size_t	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
			&& !is_operator(&input[*i])
				&& !is_quote(input[*i]))
					(*i)++;
	return (ft_substr(input, start, *i - start));
}

char	*quoted_part(char *input, size_t *i, int *expand, char *value) //ok
{
	char *part;
	char *tmp;
	int part_expand;

	part = extract_quoted_value(input, i, &part_expand);
	if (!part)
	{
		free(value);
		return (NULL);
	}
	if (part_expand)
		*expand = 1;
	tmp = join_and_free(value, part);
	return (tmp);
}

char	*process_input(char *input, size_t *i, int *expand, char *value) //ok
{
	char	*part;

	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(&input[*i]))
	{
		if (is_quote(input[*i]))
		{
			value = quoted_part(input, i, expand, value);
			if (!value)
				return (NULL);
		}
		else
		{
			part = extract_part(input, i);
			if (!part)
			{
				free(value);
				print_error(E_NOMEM, NULL, 11);
				return (NULL);
			}
			value = join_and_free(value, part);
			if (!value)
				return (NULL);
		}
	}
	return (value);
}


char	*extract_word_value(char *input, size_t *i, int *expand) //ok
{
	char	*value;

	if (!input || !i || !expand)
		return (NULL);
	value = ft_strdup("");
	if (!value)
	{
		print_error(E_NOMEM, NULL, 11);
		return (NULL);
	}
	value = process_input(input, i, expand, value);
	if (!value)
		return (NULL);
	return (value);
}
/******* ok*/

// tokenisation
void add_word_token(t_token **tokens, char *input, size_t *i) //ok
{
	char	*value;
	t_token	*new_token;
	int		expand;

	if (!tokens)
	{
		//  printf("LOG: tokens pointer is NULL\n");
		 return ;
	}
	expand = 0;
	value = extract_word_value(input, i, &expand);
	if (!value)
	{
		// printf("LOG: extract_word_value returned NULL. Freeing tokens...\n");
		free_token_list(*tokens);
		*tokens = NULL;
		return ;
	}
	// printf("LOG: Extracted word value: [%s]\n", value);
	new_token = create_token(TOKEN_WORD, value, expand);
	free(value);
	if (!new_token)
	{
		//  printf("LOG: create_token failed. Freeing tokens...\n");
		free_token_list(*tokens);
		*tokens = NULL;
		return ;
	}
	// printf("LOG: ALLOCATED new_token at %p, value: [%s], expand: %d\n", (void *)new_token, new_token->value, new_token->expand);
	add_token(tokens, new_token);
}

// redirection not supported!!!

int consecutive_redir_in(const char *input) //ok
{
    size_t	count;

	count = 0;
    while (input[count] == '<')
        count++;
    if (count == 3 || count > 5)
    {
        print_error(E_SYNTAX, "Unsupported redirection", 2);
        return (1);
    }
    if (count == 4)
    {
        print_error(E_SYNTAX, "<", 2);
        return (1);
    }
    if (count == 5)
    {
        print_error(E_SYNTAX, "<<", 2);
        return (1);
    }
    return (0);
}

int	unsupported_redirs(const char *input) //ok
{
    int					i;
	int					len;
	static const char	*redirs[] = {
        "2>", "2>>", ">&", "&>", "&>>", NULL
    };

	i = 0;
	len = ft_strlen(redirs[i]);
    while (redirs[i])
    {
        if (ft_strncmp(input, redirs[i], len) == 0)
        {
            print_error(E_SYNTAX, "Unsupported redirection", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

int	is_unsup_simple_redir(const char *input) //ok
{
	if (consecutive_redir_in(input))
		return (1);
	if (unsupported_redirs(input))
		return (1);
	return (0);
}

int	is_unsup_output_redir(const char *input) //ok
{
	if (isdigit(input[0]) && input[1] == '>')
	{
		if (input[2] == '&' && (isdigit(input[3]) || input[3] == '-'))
		{
			print_error(E_SYNTAX, "Unsupported redirection", 2);
			return (1); // Cas `n>&m` ou `n>&-`
		}
		if (input[2] == '&')
		{
			print_error(E_SYNTAX, "Unsupported redirection", 2);
			return (1); // Cas `>&n`
		}
		print_error(E_SYNTAX, "Unsupported redirection", 2);
		return (TOKEN_UNKNOWN);
	}
	return (0);
}

int is_unsup_input_redir(const char *input) //ok
{
	if (isdigit(input[0]) && input[1] == '<')
	{
		if (input[2] == '&' && (isdigit(input[3]) || input[3] == '-'))
		{
			print_error(E_SYNTAX, "Unsupported redirection", 2);
			return (1); // Cas `n<&m` ou `n<&-`
		}
		print_error(E_SYNTAX, "Unsupported redirection", 2);
		return (TOKEN_UNKNOWN);
	}
	if (input[0] == '<' && input[1] == '&' && isdigit(input[2]))
	{
		print_error(E_SYNTAX, "Unsupported redirection", 2);
		return (1); // Cas `<&n`
	}
	return (0);
}


int is_unsup_descriptor_redir(const char *input) //ok
{
	if (is_unsup_output_redir(input))
		return (1);
	if (is_unsup_input_redir(input))
		return (1);
	return (0);
}


t_token_type invalid_redir(const char *input) //ok
{
	if (is_unsup_simple_redir(input))
		return (TOKEN_UNKNOWN);
	if (is_unsup_descriptor_redir(input))
		return (TOKEN_UNKNOWN);
	return (TOKEN_WORD);
}


// validation

int check_tokens_validity(t_token *tokens) //ok
{
	while (tokens)
	{
		if (tokens->type == TOKEN_UNKNOWN)
		{
			print_error(E_SYNTAX, tokens->value, 2);
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

// valid operator

int is_logical_op(t_token_type type) //ok
{
	return (type == TOKEN_AND || type == TOKEN_OR);
}

int is_pipe_op(t_token_type type) //ok
{
	return (type == TOKEN_PIPE);
}

int validate_operator(t_token *prev, t_token *current) //ok
{
	if (is_pipe_op(current->type) || is_logical_op(current->type))
	{
		if (!prev || prev->type == TOKEN_PIPE || prev->type == TOKEN_AND ||
			prev->type == TOKEN_OR || prev->type == TOKEN_LPAREN)
		{
			print_error(E_SYNTAX, current->value, 2);
			return (0);
		}
		if (!current->next || current->next->type == TOKEN_PIPE ||
			current->next->type == TOKEN_AND || current->next->type == TOKEN_OR ||
			current->next->type == TOKEN_RPAREN)
		{
			print_error(E_SYNTAX, current->value, 2);
			return (0);
		}
	}
	return (1);
}

int check_operators(t_token *tokens) //ok
{
	t_token *prev = NULL;

	while (tokens)
	{
		if (!validate_operator(prev, tokens))
			return (0);
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}


//valid redir
int valid_general_redir(t_token *token) //ok
{
	if (!token->next)
	{
		print_error(E_SYNTAX, "newline", 2);
		return (0);
	}
	 if (token->type == TOKEN_REDIRECT_OUT || token->type == TOKEN_APPEND ||
        token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_HEREDOC)
    {
        if (token->next->type == TOKEN_PIPE)
        {
            print_error(E_SYNTAX, "|", 2);
            return (0);
        }
    }
	if (token->next->type != TOKEN_WORD && token->next->type != TOKEN_PIPE)
	{
		print_error(E_SYNTAX, token->next->value, 2);
		return (0);
	}
	return (1);
}

int validate_force_overwrite(t_token *token) //ok
{
	if (ft_strncmp(token->value, ">|", 2) == 0)
	{
		if (!token->next || token->next->type != TOKEN_WORD)
		{
			print_error(E_SYNTAX, "newline", 2);
			return (0);
		}
	}
	return (1);
}

// int validate_redirect_rw(t_token *token)
// {
//     if (ft_strncmp(token->value, "<>", 2) == 0)
// 	{
// 		if (!token->next || token->next->type != TOKEN_WORD)
// 		{
// 			print_error(E_SYNTAX, "newline", 2);
// 			return (0);
// 		}
// 	}
//     return (1);
// }

int check_redirections(t_token *tokens) //ok
{
	while (tokens)
	{
		if (tokens->type == TOKEN_REDIRECT_OUT || tokens->type == TOKEN_APPEND
			|| tokens->type == TOKEN_REDIRECT_IN || tokens->type == TOKEN_HEREDOC)
		{
			// general
			if (!valid_general_redir(tokens))
				return (0);

			// specific for `>|`
			if (tokens->type == TOKEN_REDIRECT_OUT 
				&& !validate_force_overwrite(tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

//valid parenthese

//ok

static int process_substitution(t_token *token) // ok
{
	if (token->type == TOKEN_WORD && token->value && 
		token->value[0] == '$' && token->next && token->next->type == TOKEN_LPAREN)
	{
		if (token->next->next && token->next->next->type == TOKEN_WORD)
		{
			print_error(E_SYNTAX, "substitution not supported", 258);
			return (0);
		}
	}
	return (1);
}

static int open_parenthesis(t_token *token, int *count) //ok
{
    (*count)++;
    if (token->next && token->next->type == TOKEN_RPAREN)
    {
        print_error(E_SYNTAX, ")", 258);
        return (0);
    }
    return (1);
}

static int close_parenthesis(t_token *token, int *count) //ok
{
    (*count)--;
    if (token->next && token->next->type == TOKEN_LPAREN)
    {
        print_error(E_SYNTAX, "(", 258);
        return (0);
    }
    if (*count < 0)
    {
        print_error(E_SYNTAX, ")", 258);
        return (0);
    }
    return (1);
}


static int process_parenthesis(t_token *token, int *count) //ok
{
    if (!process_substitution(token))
        return (0);

    if (token->type == TOKEN_LPAREN)
        return open_parenthesis(token, count);

    if (token->type == TOKEN_RPAREN)
        return close_parenthesis(token, count);

    return (1);
}


static int validate_parenthesis_count(t_token *tokens, int *count) //ok
{
	while (tokens)
	{
		if (!process_parenthesis(tokens, count))
			return (0);
		tokens = tokens->next;
	}
	if (*count != 0)
	{
		print_error(E_SYNTAX, "unmatched parenthesis", 258);
		return (0);
	}
	return (1);
}


static t_token *find_matching_rparen(t_token *start) //ok
{
    t_token *it;

	it = start;
    while (it)
    {
        if (it->type == TOKEN_RPAREN)
            return (it);
        it = it->next;
    }
    return (NULL);
}

static t_token *get_disallowed(t_token *tokens) //ok
{
    t_token	*cur;
    t_token *closing;
    t_token *next_token;

	cur = tokens;
    while (cur)
    {
        if (cur->type == TOKEN_LPAREN)
        {
            closing = find_matching_rparen(cur->next);
            if (closing)
            {
                next_token = closing->next;
                if (next_token && next_token->type == TOKEN_WORD)
                {
                    return (next_token); 
                }
            }
        }
        cur = cur->next;
    }
    return (NULL);
}

static int is_disallowed(t_token *tokens) //ok
{
    t_token	*bad_token;

	bad_token = get_disallowed(tokens);
    if (bad_token)
    {
        print_error(E_SYNTAX, bad_token->value, 2);
        return (1);
    }
    return (0);
}

int check_parentheses(t_token *tokens) //ok
{
	int count;

	count = 0;
	if (!validate_parenthesis_count(tokens, &count))
		return (0);
	 if (is_disallowed(tokens))
        return (0);
	return (1);
}

int validate_syntax(t_token *tokens) //ok
{
	if (!tokens)
		return (0);
	if (!check_operators(tokens))
		return (0);
	if (!check_redirections(tokens))
		return (0);
	if (!check_parentheses(tokens))
		return (0);
	if (!check_tokens_validity(tokens))
		return (0);
	return (1);
}



//******************************* */
//lexer

static t_token	*tokenize_input(char *input) //ok
{
	t_token	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		if (ft_isspace(input[i]))
			i++;
		if (invalid_redir(&input[i]) == TOKEN_UNKNOWN)
		{
			free_token_list(tokens);
			return (NULL);
		}
		else if (is_operator(&input[i]))
			add_operator_token(&tokens, input, &i);
		else
			add_word_token(&tokens, input, &i);
		while (input[i] && input[i] != '\n' && ft_isspace(input[i]))
			i++;
	}
	return (tokens);
}

static int validate_tokens(t_token *tokens) //ok
{
	if (!tokens)
		return (0);
	if (!validate_syntax(tokens))
		return (0);
	return (1);
}

static int is_double_parentheses_case(const char *input) //ok
{
	if (input[0] == '(' && input[1] == '(')
    {
        const char	*closing;
		const char	*content;
    
        closing = input + 2;
        while (*closing && *closing != ')')
            closing++;
        if (*closing == ')' && *(closing + 1) == ')')
        {
            content = input + 2;
            while (content < closing)
            {
                if (!ft_isspace(*content))
                    return (1);
                content++;
            }
        }
    }
	return (0);
}

static int special_cases(char *input) //ok
{
    while (*input && ft_isspace(*input))
        input++;
    if (*input == '\0')
        return (1);
    if ((input[0] == ':' || input[0] == '!')
		&& (input[1] == '\0' || input[1] == ' '))
			return (1);
	if (is_double_parentheses_case(input))
        return (1);
    return (0);
}

t_token *lexer(char *input)
{
	t_token	*tokens;

	if (!input || *input == '\0')
		return (NULL); // code error
	if (special_cases(input))
	{
		printf("check %s\n", input);
		return (NULL);
	}
	tokens = tokenize_input(input);
	if (!tokens)
		return (NULL);
	if (!validate_tokens(tokens))
	{
		free_token_list(tokens);
		return (NULL);
	}
	return (tokens);
}
//******************************* */

		// Expand

//******************************* */


// utils

char *compare(char *key, t_env_var *env)
{
    t_env_var *temp;
	char *value;

    temp = env;
    while (temp)
    {
        if (ft_strncmp(key, temp->key, ft_strlen(temp->key)) == 0
			&& ft_strlen(key) == ft_strlen(temp->key))
        {
            value = ft_strdup(temp->value);
            // free(key);
            return (value);
        }
        temp = temp->next;
    }
    // free(key);
    return ft_strdup("");
}

char *ft_strjoin_free(char *s1, char *s2, int free_flag)
{
    char	*result;
    size_t	len1;
    size_t	len2;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    result = malloc(len1 + len2 + 1);
    if (!result)
        return (NULL);
    ft_memcpy(result, s1, len1);
    ft_memcpy(result + len1, s2, len2);
    result[len1 + len2] = '\0';
    if (free_flag == 1 || free_flag == 3)
        free(s1);
    if (free_flag == 2 || free_flag == 3)
        free(s2);
    return (result);
}

char *ft_strjoin_char(char *s, char c)
{
    size_t len = ft_strlen(s);
    char *new_str = malloc(len + 2);
    if (!new_str)
        return (NULL);
    ft_strlcpy(new_str, s, len + 1);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return (new_str);
}


int is_single_quoted(const char *str)
{
    size_t len;

    if (!str)
        return (0);
    len = ft_strlen(str);
    return (len >= 2 && str[0] == '\'' && str[len - 1] == '\'');
}


//expander ok

static char	*append_exit_status(char *result, t_minishell *shell)
{
    char	*exit_status;
    char	*temp;

	exit_status = ft_itoa(shell->last_exit_status);
    if (!exit_status)
    {
        free(result);
        return (NULL);
    }
    temp = ft_strjoin(result, exit_status);
    free(exit_status);
    free(result);
    return (temp);
}

static size_t skip_and_get_var_length(const char *src, size_t *i)
{
    size_t  start;

	(*i)++;         // Sauter le caractère '$'
	start = *i;     
	while (src[*i] && (ft_isalnum(src[*i]) || src[*i] == '_'))
		(*i)++;
	return (*i - start); 
}

static char	*join_var_value(t_varinfo var, char *result, t_minishell *shell)
{
    char	*var_name;
    char	*var_value;
    char	*temp;

    var_name = ft_substr(var.src, var.start, var.len);
    if (!var_name)
    {
        free(result);
        return (NULL);
    }
    var_value = compare(var_name, shell->env_list);
    free(var_name);
    if (!var_value)
        var_value = ft_strdup("");
    temp = ft_strjoin(result, var_value);
    free(var_value);
    free(result);
    return (temp);
}

static char *handle_empty_var_name(char *result)
{
    char *temp;

    temp = ft_strjoin_char(result, '$');
    free(result);
    return (temp);
}


static char *append_var_value(const char *src, size_t *i, char *result, t_minishell *shell)
{
	t_varinfo   var;
	size_t      len;

	len = skip_and_get_var_length(src, i);
	var.src = src;
	var.start = (*i) - len;  // Position du début de la variable
	var.len = len;
	if (len > 0)
		return (join_var_value(var, result, shell));
	else
		return (handle_empty_var_name(result));
}


static char *append_char_to_result(char *result, char c)
{
    char	*temp;

	temp = ft_strjoin_char(result, c);
	free(result);
	return (temp);
}

static char *process_dollar(const char *src, size_t *i, char *result, t_minishell *shell)
{
    if (src[*i + 1] == '?')
    {
		result = append_exit_status(result, shell);
		if (!result)
			return (NULL);
		*i += 2; // Sauter '$?'
	}
	else
	{
		result = append_var_value(src, i, result, shell);
		if (!result)
			return (NULL);
	}
	return (result);
}

static char	*process_normal_char(const char *src, size_t *i, char *result)
{
	result = append_char_to_result(result, src[*i]);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}

char *expand_variables_in_str(const char *src, t_minishell *shell)
{
    size_t	i;
    char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
		{
			result = process_dollar(src, &i, result, shell);
			if (!result)
				return (NULL);
		}
		else
		{
			result = process_normal_char(src, &i, result);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}

static int expand_single_token(t_token *token, t_token *tokens, t_minishell *shell)
{
	char	*expanded;

	if (token->type == TOKEN_WORD)
	{
		if (token->expand == 1 || (strchr(token->value, '$') 
			&& !is_single_quoted(token->value)))
		{
			expanded = expand_variables_in_str(token->value, shell);
			if (!expanded)
			{
				fprintf(stderr, "Error: Memory allocation failed during variable expansion.\n");
				free_token_list(tokens);
				shell->running = 0;
				return (0);  // Erreur => on arrête
			}
			free(token->value);
			token->value = expanded;
		}
	}
	return (1);
}

void expand_token_list(t_token *tokens, t_minishell *shell)
{
	t_token *current = tokens;

	while (current)
	{
		if (!expand_single_token(current, tokens, shell))
			return ;
		current = current->next;
    }
}


//----------------------------------------------------------------




//content heredoc  // OK


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

t_hdc	*init_heredoc(void)
{
	t_hdc	*content;

	content = malloc(sizeof(t_hdc));
	if (!content)
		return (NULL);
	content->lines = NULL;
	content->count = 0;
	return (content);
}

char	**split_lines(const char *input)
{
	char	**lines;

	lines = ft_split(input, '\n');
	if (!lines)
		return (NULL);
	return (lines);
}

static char **dup_lines(t_hdc *content, const char *line)
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


int	get_lines(t_hdc *content, char **lines, const char *delim)
{
	size_t	i;

	i = 1;
	while (lines[i])
	{
		if (add_line(content, lines[i]) == -1)
		{
			free_heredoc_content(content);
			return (-1);
		}
		if (ft_strcmp(lines[i], delim) == 0)
			return (0);
		i++;
	}
	return (0);
}

// get content heredocs copy-paster
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

//print heredoc
void	process_heredoc(const t_token *tokens, const char *input)
{
	const t_token		*current;
	t_hdc	*content;
	char				*delim;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (current->next)
				delim = current->next->value;
			else
				delim = NULL;
			if (delim)
			{
				printf("Handling heredoc with delim: %s\n", delim);
				content = get_heredoc_lines(input, delim);
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




const char *get_token_type_name(t_token_type type) //ok
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



void	print_tokens(t_token *tokens) //ok
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


/* ********************************************* */
//free


/*
void free_command(t_command *cmd)
{
	t_redir *redir;
	t_redir *next;
	int i;

	if (!cmd)
		return;

	i = 0;
	while (i < cmd->argc)
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);

	redir = cmd->redirs;
	while (redir)
	{
		next = redir->next;
		free(redir->filename);

		if (redir->type == REDIR_HEREDOC && redir->content)
		{
			free_heredoc_content(redir->content);
			free(redir->content);
		}
		free(redir);
		redir = next;
	}
	free(cmd);
}


void free_ast(t_ast *node)
{
	if (!node)
		return ;

	if (node->type == NODE_COMMAND)
		free_command(node->command);

	free_ast(node->left);
	free_ast(node->right);

	free(node);
}
*/



//utils

// goto token

static t_token	*parser_advance(t_parser *parser) //ok
{
	t_token	*current;

	current = parser->current;
	if (parser->current)
		parser->current = parser->current->next;
	return (current);
}

// check one token

static int	is_token(t_parser *parser, t_token_type type) //ok
{
    return (parser->current && parser->current->type == type);
}

// update quote

static size_t	process_quotes(const char *value, char *result, size_t i, size_t *j) //ok
{
    char	quote;

	quote = value[i];
	i++;
	while (value[i] && value[i] != quote)
		result[(*j)++] = value[i++];
	if (value[i] == quote)
		i++;
	return (i);
}

static char	*clean_quotes(const char *value) //ok
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!value)
		return (NULL);
	len = ft_strlen(value);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
			i = process_quotes(value, result, i, &j);
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
	return (result);
}



/***********************************************/

// create node

t_ast	*create_ast_node(t_node_type type) //ok
{
    t_ast	*node;

	node = malloc(sizeof(t_ast));
    if (!node)
    {
        perror("Error allocating memory for AST node");
        return (NULL);
    }
    node->type = type;
    node->command = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

// free

void free_ast(t_ast *node)
{
	int i;

    if (!node)
        return ;
    free_ast(node->left);
    free_ast(node->right);
    if (node->command)
    {
		i = 0;
        while (node->command->argv && node->command->argv[i])
		{
			free(node->command->argv[i]);
			i++;
		}
        free(node->command->argv);
        t_redir *redir = node->command->redirs;
        while (redir)
        {
            t_redir *next = redir->next;
            free(redir->filename);
			if (redir->content) 
			{
				free_heredoc_content(redir->content);
				free(redir->content);
			}
				
            free(redir);
            redir = next;
        }
        free(node->command);
    }
    free(node);
}



// grammar

//1 Liste principale

// refactorized [main list]
t_ast	*parse_init_pipe(t_parser *parser, char *input) //ok
{
	t_ast	*node_pipe;

	node_pipe = parse_pipe(parser, input);
	if (!node_pipe)
	{
		perror("Invalid pipeline or subshell");
		return (NULL);
	}
	return (node_pipe);
}

t_ast	*parse_op(t_token_type operator, t_ast *left, t_ast *right) //ok
{
	t_ast	*logic_node;

	if (operator == TOKEN_AND)
		logic_node = create_ast_node(NODE_AND);
	else
		logic_node = create_ast_node(NODE_OR);
	if (!logic_node)
	{
		perror("Failed to create AST node for conditional operator"); //ok
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	logic_node->left = left;
	logic_node->right = right;
	return (logic_node);
}

t_ast	*parse_logical(t_parser *parser, char *input, t_ast *pipe_node) //ok
{
	t_token_type	operator;
	t_ast			*right;
	t_ast			*logic_node;

	while (is_token(parser, TOKEN_AND) || is_token(parser, TOKEN_OR))
	{
		operator = parser->current->type;
		parser_advance(parser);
		right = parse_pipe(parser, input);
		if (!right)
		{
			perror("Invalid pipeline after conditional operator");
			free_ast(pipe_node);
			return (NULL);
		}
		logic_node = parse_op(operator, pipe_node, right);
		if (!logic_node)
			return (NULL);
		pipe_node = logic_node;
	}
	return (pipe_node);
}

t_ast	*parse_list(t_parser *parser, char *input)
{
	t_ast	*pipe_node;

	pipe_node = parse_init_pipe(parser, input);
	if (!pipe_node)
		return (NULL);
	pipe_node = parse_logical(parser, input, pipe_node);
	return (pipe_node);
}



// 2 refactoring pipe

t_ast	*create_pipe_node(t_ast *cmd, t_ast *next_pipeline) //ok
{
	t_ast	*pipe_node;

	pipe_node = malloc(sizeof(t_ast));
	if (!pipe_node)
	{
		free_ast(cmd);
		free_ast(next_pipeline);
		return (NULL);
	}
	pipe_node->type = NODE_PIPE;
	pipe_node->left = cmd;
	pipe_node->right = next_pipeline;
	pipe_node->command = NULL;
	return (pipe_node);
}

t_ast	*parse_pipe(t_parser *parser, char *input) //ok
{
	t_ast	*cmd;
	t_ast	*next_pipeline;
	t_ast	*pipe_node;

	cmd = parse_cmd(parser, input);
	if (!cmd)
		return (NULL);
	if (is_token(parser, TOKEN_PIPE))
	{
		parser_advance(parser);
		next_pipeline = parse_pipe(parser, input);
		if (!next_pipeline)
		{
			print_error(E_PIPE, parser->current->value, 9);
			free_ast(cmd);
			return (NULL);
		}
		pipe_node = create_pipe_node(cmd, next_pipeline);
		return (pipe_node);
	}
	return (cmd);
}



// 3 refactory cmd
t_ast	*create_cmd_node(void) //ok
{
	t_ast	*cmd;

	cmd = malloc(sizeof(t_ast));
	if (!cmd)
		return (NULL);

	cmd->type = NODE_COMMAND;
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->command = NULL;

	return (cmd);
}

t_ast	*parse_cmd(t_parser *parser, char *input) //ok
{
	t_ast	*cmd;

	if (is_token(parser, TOKEN_LPAREN))
		return (parse_subshell(parser, input));
	cmd = create_cmd_node();
	if (!cmd)
		return (NULL);
	cmd->command = parse_simple_cmd(parser, input);
	if (!cmd->command)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}



// 4 - refactoring: Simple Command
static t_command *create_cmd(void) //ok
{
    t_command	*cmd;

	cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->argc = 0;
    cmd->redirs = NULL;
    return (cmd);
}

static char **expand_argv(t_command *cmd, char *new_arg) //ok
{
    char **new_argv;
    int   i;

    new_argv = malloc(sizeof(char *) * (cmd->argc + 2));
    if (!new_argv)
        return NULL;
    i = 0;
    while (i < cmd->argc)
    {
        new_argv[i] = cmd->argv[i];
        i++;
    }
    free(cmd->argv);
    new_argv[cmd->argc++] = new_arg;
    new_argv[cmd->argc] = NULL;
    return (new_argv);
}

static int handle_word_token(t_parser *parser, t_command *cmd) //ok
{
    char	*cleaned_value;
    char	**new_argv;

    cleaned_value = clean_quotes(parser->current->value);
    if (!cleaned_value)
    {
        print_error(E_NOMEM, "Memory allocation failed", 1);
        return (-1);
    }
    new_argv = expand_argv(cmd, cleaned_value);
    if (!new_argv)
    {
        print_error(E_NOMEM, "Memory allocation failed", 1);
        free(cleaned_value);
        return (-1);
    }
    cmd->argv = new_argv;
    parser_advance(parser);
    return (0);
}


static int handle_redirection(t_parser *parser, t_command *cmd, char *input) //ok
{
    t_redir	*redir;

    redir = parse_io_redirect(parser, input);
    if (!redir)
    {
        free(cmd->argv);
        return (-1);
    }
    redir->next = cmd->redirs;
    cmd->redirs = redir;
    return (0);
}

static int process_token(t_parser *parser, t_command *cmd, char *input) //ok
{
    if (is_token(parser, TOKEN_WORD))
    {
        if (handle_word_token(parser, cmd) == -1)
            return (-1);
    }
    else if (is_token(parser, TOKEN_REDIRECT_IN)
             || is_token(parser, TOKEN_REDIRECT_OUT)
             || is_token(parser, TOKEN_APPEND)
             || is_token(parser, TOKEN_HEREDOC))
    {
        if (handle_redirection(parser, cmd, input) == -1)
            return (-1);
    }
    else
        return (1);
    return (0);
}


t_command *parse_simple_cmd(t_parser *parser, char *input) //ok
{
    t_command *cmd;
    int        result;

    cmd = create_cmd();
    if (!cmd)
        return (NULL);
    while (parser->current)
    {
        result = process_token(parser, cmd, input);
        if (result == -1)
        {
            free(cmd);
            return (NULL);
        }
        else if (result == 1)
            break ;
    }
    return (cmd);
}




// 5 Redirections [refactor]

t_redir_type convert_token_to_redir_type(t_token_type token_type) //ok
{
	if (token_type == TOKEN_REDIRECT_IN)
		return REDIR_IN;
	if (token_type == TOKEN_REDIRECT_OUT)
		return REDIR_OUT;
	if (token_type == TOKEN_APPEND)
		return REDIR_APPEND;
	if (token_type == TOKEN_HEREDOC)
		return REDIR_HEREDOC;
	return (REDIR_INVALID);
}

static t_redir *create_redir(void) //ok
{
    t_redir	*redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = REDIR_INVALID;
    redir->filename = NULL;
    redir->content = NULL;
    redir->next = NULL;
    return (redir);
}

static int validate_redir_token(t_parser *parser, t_redir *redir) //ok
{
    t_token	*redir_token;

    redir_token = parser_advance(parser);
    if (!redir_token || !is_token(parser, TOKEN_WORD))
    {
        perror("Redirection error: missing or invalid token");
        return (-1);
    }
    redir->type = convert_token_to_redir_type(redir_token->type);
    if (redir->type == REDIR_INVALID)
    {
        perror("Invalid redirection type");
        return (-1);
    }
    return (0);
}

static int handle_heredoc(t_parser *parser, t_redir *redir, char *input) //ok
{
    printf("Parsing heredoc with delim: %s\n", parser->current->value);
    redir->filename = ft_strdup(parser->current->value);
    if (!redir->filename)
    {
        perror("Failed to allocate memory for heredoc filename");
        return (-1);
    }
    redir->content = get_heredoc_lines(input, parser->current->value);
    if (!redir->content)
    {
        perror("Failed to parse heredoc content");
        free(redir->filename);
        return (-1);
    }
    parser_advance(parser);
    return (0);
}

static int process_redirection(t_parser *parser, t_redir *redir, char *input) //ok
{
    if (redir->type == REDIR_HEREDOC)
    {
        if (handle_heredoc(parser, redir, input) == -1)
            return (-1);
    }
    else
    {
        redir->filename = ft_strdup(parser_advance(parser)->value);
        if (!redir->filename)
        {
            perror("Failed to allocate memory for filename");
            return (-1);
        }
    }
    return (0);
}

t_redir *parse_io_redirect(t_parser *parser, char *input) //ok
{
    t_redir *redir;

    redir = create_redir();
    if (!redir)
        return (NULL);
    if (validate_redir_token(parser, redir) == -1)
    {
        free(redir);
        return (NULL);
    }
    if (process_redirection(parser, redir, input) == -1)
    {
        free(redir);
        return (NULL);
    }
    return (redir);
}


// 6 Subshell [refactoring]

static int subshell_syntax(t_parser *parser, t_ast **subshell, char *input) //ok
{
    if (!is_token(parser, TOKEN_LPAREN))
        return (-1);
    parser_advance(parser);
    if (is_token(parser, TOKEN_RPAREN))
    {
        print_error(E_SYNTAX, parser->current->value, 10);
        return (-1);
    }
    *subshell = parse_list(parser, input);
    if (!(*subshell))
    {
        print_error(E_SYNTAX, parser->current->value, 10);
        return (-1);
    }
    if (!is_token(parser, TOKEN_RPAREN))
    {
        print_error(E_SYNTAX, parser->current->value, 10);
        free_ast(*subshell);
        return (-1);
    }
    parser_advance(parser);
    return (0);
}

t_ast *parse_subshell(t_parser *parser, char *input) //ok
{
    t_ast	*subshell;

	subshell = NULL;
    if (subshell_syntax(parser, &subshell, input) == -1)
        return (NULL);
    if (is_token(parser, TOKEN_WORD) || is_token(parser, TOKEN_LPAREN))
    {
        print_error(E_SYNTAX, parser->current->value, 10);
        free_ast(subshell);
        return (NULL);
    }
    return (subshell);
}


// 7 Conditionnelle [refactoring]

static t_ast *create_logic_node(t_token_type operator, t_ast *left, t_ast *right) //ok
{
    t_ast *logic_node;

    logic_node = malloc(sizeof(t_ast));
    if (!logic_node)
        return (NULL);
    if (operator == TOKEN_AND)
        logic_node->type = NODE_AND;
    else
        logic_node->type = NODE_OR;
    logic_node->left = left;
    logic_node->right = right;
    return (logic_node);
}

t_ast *parse_conditional(t_parser *parser, t_ast *left, char *input) //ok
{
    t_token_type	operator;
    t_ast			*right;

    if (is_token(parser, TOKEN_AND) 
		|| is_token(parser, TOKEN_OR))
    {
        operator = parser_advance(parser)->type;
        right = parse_pipe(parser, input);
        if (!right)
        {
            perror("conditional error");
            return (NULL);
        }
        return (create_logic_node(operator, left, right));
    }
    return (NULL);
}


// Entrée principale pour le parsing

t_ast	*parse(t_token *tokens, char *input) //ok
{
    t_parser	parser;
	t_ast		*root;

	parser.current = tokens;
	root = parse_list(&parser, input);
	if (root && parser.current != NULL)
    {
        perror("Unexpected token at end of input");
        free_ast(root);
        root = NULL;
    }
    return (root);
}








// -------PRINT-------------

void print_indentation(int depth) //ok
{
	int	i;

	i = 0;
	while (i < depth)
	{
		 printf("  ");
		 i++;
	}
}

static void print_node_type(t_ast *ast) //ok
{
    if (ast->type == NODE_COMMAND)
        printf("NODE_COMMAND: ");
    else if (ast->type == NODE_PIPE)
        printf("NODE_PIPE: ");
    else if (ast->type == NODE_AND)
        printf("NODE_AND: ");
    else if (ast->type == NODE_OR)
        printf("NODE_OR: ");
    else if (ast->type == NODE_SUBSHELL)
        printf("NODE_SUBSHELL: ");
    else
        printf("UNKNOWN NODE: ");
}

static void print_command_args(t_command *command) //ok
{
    int i = 0;

    if (!command)
        return;
    printf("[ ");
    while (i < command->argc)
    {
        printf("%s ", command->argv[i]);
        i++;
    }
    printf("]\n");
}

static void heredoc_content(t_redir *redir, int depth) //ok
{
    size_t j;

    if (redir->content)
    {
        j = 0;
        while (j < redir->content->count)
        {
            print_indentation(depth + 2);
            printf("Line %zu: %s\n", j + 2, redir->content->lines[j]);
            j++;
        }
    }
}

static void print_redirections(t_redir *redir, int depth) //ok
{
    while (redir)
    {
        print_indentation(depth + 1);

        if (redir->type == REDIR_IN)
            printf("REDIR_IN: %s\n", redir->filename);
        else if (redir->type == REDIR_OUT)
            printf("REDIR_OUT: %s\n", redir->filename);
        else if (redir->type == REDIR_APPEND)
            printf("REDIR_APPEND: %s\n", redir->filename);
        else if (redir->type == REDIR_HEREDOC)
        {
            printf("REDIR_HEREDOC: %s\n", redir->filename);
            heredoc_content(redir, depth);
        }
        redir = redir->next;
    }
}

void print_ast(t_ast *ast, int depth) //ok
{
    if (!ast)
        return;
    print_indentation(depth);
    print_node_type(ast);
    if (ast->type == NODE_COMMAND && ast->command)
    {
        print_command_args(ast->command);
        print_redirections(ast->command->redirs, depth);
    }
    else
        printf("\n");
    print_ast(ast->left, depth + 1);
    print_ast(ast->right, depth + 1);
}











// cd ok

// char	*get_env_value(const char *key, t_env_var *env_list)
// {
// 	t_env_var	*current;

// 	current = env_list;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, key) == 0)
// 			return (ft_strdup(current->value));
// 		current = current->next;
// 	}
// 	return (NULL);
// }

char	*get_env_cd(const char *key, t_env_var *env_list)
{
	t_env_var	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/*----------------------*/

static int update_env_value_if_exists(t_env_var *env_list, const char *key, const char *value)
{
    t_env_var	*current;

	current = env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            if (!current->value)
            {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            return (1);
        }
        current = current->next;
    }
    return (0);
}


static t_env_var *create_new_env_node(const char *key, const char *value)
{
    t_env_var *new_node = malloc(sizeof(t_env_var));
    if (!new_node)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;
    if (!new_node->key || !new_node->value)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        exit(EXIT_FAILURE);
    }
    return (new_node);
}


static void append_env_node(t_env_var **env_list, t_env_var *new_node)
{
	 t_env_var *current;

    if (!*env_list)
	{
        *env_list = new_node;
        return ;
    }
    current = *env_list;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

// Et dans set_env_value :




void set_env_value(t_env_var **env_list, const char *key, const char *value)
{
	t_env_var	*new_node;

    if (update_env_value_if_exists(*env_list, key, value))
        return ;
    // Crée un nouveau nœud
    new_node = create_new_env_node(key, value);
    append_env_node(env_list, new_node);
}

/*------------------------------*/
static void update_env_pwd(t_minishell *shell)
{
    char	*oldpwd_value;
    char	*newpwd_value;

	oldpwd_value = get_env_cd("PWD", shell->env_list);
	newpwd_value = getcwd(NULL, 0);
	if (oldpwd_value)
	{
		set_env_value(&shell->env_list, "OLDPWD", oldpwd_value);
		// free(oldpwd_value);
	}
	if (newpwd_value)
	{
		set_env_value(&shell->env_list, "PWD", newpwd_value);
		free(newpwd_value);
	}
}

// cd
static char	*get_cd_path(t_minishell *shell, char **args)
{
	char	*path;
	char	*home;

	path = NULL;
	home = NULL;
	if (!args[1])
	{
		home = get_env_cd("HOME", shell->env_list);
		if (!home)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
		}
		path = ft_strdup(home);
		free(home);
		if (!path)
		{
			fprintf(stderr, "cd: Memory allocation failed\n");
			return (NULL);
		}
	}
	else
		path = args[1]; 
	return (path);
}

static int validate_cd_path(t_minishell *shell, char *path, int duplicate_path)
{
	if (!path || ft_strlen(path) == 0)
	{
		fprintf(stderr, "cd: Invalid path\n");
		shell->last_exit_status = 1;
		if (duplicate_path)
			free(path);
		return (1);
	}
	return (0);
}

static int execute_cd(t_minishell *shell, char *path, int duplicate_path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		shell->last_exit_status = 1;
		if (duplicate_path)
			free(path);
		return (1);
	}
	update_env_pwd(shell);
	if (duplicate_path)
		free(path);

	shell->last_exit_status = 0;
	return (0);
}

int	builtin_cd(t_minishell *shell, char **args)
{
	char	*path;
	int		duplicate_path;

	duplicate_path = !args[1];
	path = get_cd_path(shell, args);
	if (!path)
		return (1);
	if (validate_cd_path(shell, path, duplicate_path))
		return (1);
	return (execute_cd(shell, path, duplicate_path));
}


/****************************************************** */


// builtins echo [ok]

static int	parse_options(char **args, int *newline)
{
	int	i;
	int	j;

	*newline = 1;
	i = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		*newline = 0;
		i++;
	}
	return (i);
}

static int	print_args(char **args, int start_index, int newline)
{
    int	i;

	i = start_index;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	builtin_echo(t_minishell *shell, char **args)
{
	int	newline;
	int	start_index;

	(void)shell;
	start_index = parse_options(args, &newline);
	return (print_args(args, start_index, newline));
}

/****************************************************** */

// env ok

int builtin_env(t_minishell *shell, char **args)
{
    t_env_var *current;

	current = NULL;
    if (args[1])
    {
        fprintf(stderr, "env: No arguments or options allowed\n");
        shell->last_exit_status = 1;
        return (1);
    }
    if (!shell->env_list)
    {
        fprintf(stderr, "env: Environment list is not initialized.\n");
        shell->last_exit_status = 1;
        return (1);
    }
    current = shell->env_list;
    while (current)
    {
        if (current->key && current->value)
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }

    shell->last_exit_status = 0;
    return (0);
}


/****************************************************** */

// exit ok

int is_valid_format(const char *str, unsigned long *value, int *sign)
{
    *sign = 1;
    *value = 0;

    if (!str || *str == '\0')
        return (0);
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            *sign = -1;
        str++;
    }
    if (!*str)
        return (0);
    while (*str)
    {
        if (!isdigit(*str))
            return (0);
        if (*value > (LONG_MAX / 10) || (*value == (LONG_MAX / 10) 
			&& (*str - '0') > (LONG_MAX % 10)))
				return (0);
        *value = *value * 10 + (*str - '0');
        str++;
    }
    return (1);
}

int is_valid_integer(const char *str, long *result)
{
	unsigned long	value;
	int				sign;

	if (!is_valid_format(str, &value, &sign))
		return (0);
	*result = sign * (long)value;
    if (*result > LONG_MAX || *result < LONG_MIN)
        return (0);
    return (1);
}

void	cleanup_shell(t_minishell *shell)
{
	// free liste var env
	free_env_list(shell->env_list);
	rl_clear_history();
	// ..
}

int builtin_exit(t_minishell *shell, char **args)
{
    long	exit_status;

    ft_putendl_fd("exit", STDOUT_FILENO);
    if (!args[1])
        exit(shell->last_exit_status);
    if (!is_valid_integer(args[1], &exit_status))
    {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putendl_fd(": numeric argument required", STDERR_FILENO);
        cleanup_shell(shell);
        exit(255);
    }
    if (args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
        shell->last_exit_status = 1;
        return (1);
    }
    exit_status = exit_status % 256;
    if (exit_status < 0)
        exit_status += 256;
    cleanup_shell(shell);
    exit((unsigned char)exit_status);
}

/**************************************** */


//export

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	display_exported_vars(t_minishell *shell)
{
	t_env_var	*current;

	current = shell->env_list;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		if (current->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}

void update_env(t_minishell *shell, const char *key, const char *value)
{
    t_env_var *current = shell->env_list;
    t_env_var *previous = NULL;
    t_env_var *new_node;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = value ? ft_strdup(value) : NULL;
            return;
        }
        if (ft_strcmp(current->key, key) > 0)
            break;

        previous = current;
        current = current->next;
    }
    new_node = malloc(sizeof(t_env_var));
    if (!new_node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_node->key = ft_strdup(key);
    new_node->value = value ? ft_strdup(value) : NULL;
    new_node->next = current;
    if (previous)
        previous->next = new_node;
    else
        shell->env_list = new_node;
}


// need refactoring
int	builtin_export(t_minishell *shell, char **args)
{
	int i;
	int status = 0;
	char *key;
	char *value;
	char *equal_sign;

	if (!args[1])
	{
		display_exported_vars(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			key = ft_substr(args[i], 0, equal_sign - args[i]);
			value = ft_strdup(equal_sign + 1);
		}
		else
		{
			key = ft_strdup(args[i]);
			value = NULL;
		}
		if (!is_valid_identifier(key))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
			free(key);
			free(value);
			i++;
			continue;
		}
		update_env(shell, key, value);
		free(key);
		free(value);
		i++;
	}
	return (status);
}
/****************************************************** */

//pwd ok[amelioration]

int	builtin_pwd(t_minishell *shell, char **args)
{
	char	*cwd;

	(void) shell;
	if (args[1])
	{
		ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		return (0);
	}
	else
	{
		ft_putstr_fd("pwd: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
}
/****************************************************** */

//unset

int	is_valid_id_unset(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_env_var(t_minishell *shell, const char *key)
{
	t_env_var	*current;
	t_env_var	*prev;

	current = shell->env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

int builtin_unset(t_minishell *shell, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_id_unset(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
			i++;
			continue ;
		}
		remove_env_var(shell, args[i]);
		i++;
	}
	return (status);
}
/****************************************************** */

// builtins main

int execute_builtin(t_minishell *shell, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return builtin_echo(shell, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		return builtin_cd(shell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		return builtin_pwd(shell, args);
	else if (ft_strcmp(args[0], "export") == 0)
		return builtin_export(shell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		return builtin_unset(shell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		return builtin_env(shell, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		return builtin_exit(shell, args);
	return (-1);
}

int is_builtin(const char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}
/****************************************************** */
// utils

//get_env_value
char	*get_env_value(const char *key, t_env_var *env_list)
{
	t_env_var	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

void	free_str_array(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*find_command_path(char *cmd_name, t_env_var *env_list)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	path_env = get_env_value("PATH", env_list);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_free(ft_strjoin(paths[i], "/"), cmd_name, 1);
		if (!full_path)
		{
			free_str_array(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_str_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_str_array(paths);
	return (NULL);
}




//content heredoc:



// Dans votre code principal (le parent)




// simple heredocs
/************************************************ */
static int check_params(t_hdc *content, const char *delim, t_minishell *shell)
{
    if (!content || !delim || !shell)
	{
        fprintf(stderr, "Invalid parameters provided to handle_interactive_heredoc.\n");
        return (0);
    }
    return (1);
}

static char *read_user_input(const char *delim, t_minishell *shell)
{
    char		*line;

	line = readline("\001"COLOR_BLUE"\002""heredoc> ""\001"COLOR_RESET"\002");
   if (!line) // EOF (Ctrl+D)
    {
        fprintf(stderr, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",
                shell->nb_line_heredoc , delim);
    }
    return (line);
}


static char *process_input_line(char *line, const char *delim, t_minishell *shell)
{
    char	*expanded_line;

	expanded_line = NULL;
    if (ft_strcmp(line, delim) == 0)
	{
        free(line);
        return (NULL);
    }
    expanded_line = expand_variables_in_str(line, shell);
    free(line);
    if (!expanded_line)
	{
        perror("expand_variables_in_str");
    }
    return (expanded_line);
}

static int append_line(t_hdc *content, char *line)
{
    char	**new_lines;
	size_t	i;

	new_lines = malloc(sizeof(char *) * (content->count + 1));
    if (!new_lines)
	{
        perror("malloc");
        free(line);
        return (0);
    }
	i = 0;
    while (i < content->count)
	{
        new_lines[i] = content->lines[i];
		i++;
    }
    new_lines[content->count] = line;
    free(content->lines);
    content->lines = new_lines;
    content->count++;
    return (1);
}

void handle_interactive_heredoc(const char *delim, t_hdc *content, t_minishell *shell)
{
	char	*line;
	char	*expanded_line;

	if (!check_params(content, delim, shell))
		return ;
	main_heredoc(); // Configure signals for heredoc mode
	while (1)
	{
		line = read_user_input(delim, shell);
		if (!line)
			break;
		expanded_line = process_input_line(line, delim, shell);
		if (!expanded_line)
			break;
		if (!append_line(content, expanded_line))
			break;
    }
}

/************************************************ */

// Multiligne heredocs

// check_params()

static int expand_existing_lines(t_hdc *content, t_minishell *shell)
{
	char	*expanded_line;
	size_t	i;

	i = 0;
    while (i < content->count)
	{
        expanded_line = expand_variables_in_str(content->lines[i], shell);
        if (!expanded_line)
		{
            perror("expand_variables_in_str");
            return 0;
        }
        free(content->lines[i]);
        content->lines[i] = expanded_line;
		i++;
    }
    return (1);
}

static int read_and_expand(t_hdc *content, const char *delim, t_minishell *shell)
{
	char	*expanded_line;
	char	*line;

    while (1)
	{
		line = read_user_input(delim, shell);
		if (!line)
			break ;
        if (ft_strcmp(line, delim) == 0)
		{
            free(line);
            break ;
        }
        expanded_line = expand_variables_in_str(line, shell);
        free(line);
        if (!expanded_line)
            return (0);
        if (!append_line(content, expanded_line))
		{
            free(expanded_line);
            return (0);
        }
    }
    return (1);
}

static void remove_final_delimiter(t_hdc *content, const char *delim)
{
    if (content->count > 0 
		&& ft_strcmp(content->lines[content->count - 1], delim) == 0)
	{
        free(content->lines[content->count - 1]);
        content->lines[content->count - 1] = NULL;
        content->count--;
    }
}

void handle_copied_heredoc(t_hdc *content, const char *delim, t_minishell *shell)
{
    if (!check_params(content, delim, shell))
		return ;
	main_heredoc(); // Configure signals for heredoc mode
    if (!expand_existing_lines(content, shell))
		return ;
    if (content->count == 0 
		|| ft_strcmp(content->lines[content->count - 1], delim) != 0)
		{
			if (!read_and_expand(content, delim, shell))
				return ;
    }
    remove_final_delimiter(content, delim);
}


/************************************************ */



// static int handle_redir_in(t_redir *current)
// {
//     int	fd;

// 	fd = open(current->filename, O_RDONLY);
//     if (fd == -1 )
// 	{
//        // Si le fichier n'existe pas ou n'est pas accessible
//         fprintf(stderr, "minishell: %s: No such file or directory\n", current->filename);
//         return (-1);
//     }
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 	{
// 		perror("dup2");
//         close(fd);
//         return (-1);
// 	}
//     close(fd);
//     return (0);
// }


static int handle_redir_in(t_redir *current)
{
    int	fd;

	fd = open(current->filename, O_RDONLY);
    if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
	{
        perror(current->filename);
        if (fd != -1)
            close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

static int handle_redir_out(t_redir *current)
{
    int fd;

	fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
        perror(current->filename);
        if (fd != -1)
            close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}


static int handle_redir_append(t_redir *current)
{
    int fd;

	fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1) {
        perror(current->filename);
        if (fd != -1)
            close(fd);
        return -1;
    }
    close(fd);
    return (0);
}


static int setup_heredoc_content_pipe(t_redir *current)
{
    int		pipefd[2];
    size_t	i;

    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        return (-1);
    }
    i = 0;
    while (i < current->content->count)
	{
        write(pipefd[1], current->content->lines[i], ft_strlen(current->content->lines[i]));
        write(pipefd[1], "\n", 1);
        i++;
    }
    close(pipefd[1]);
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
        perror("dup2");
        close(pipefd[0]);
        return (-1);
    }
    close(pipefd[0]);
    return (0);
}

static int handle_redir_heredoc(t_redir *current, t_minishell *shell)
{
    if (!current->content)
	{
        fprintf(stderr, "minishell: HEREDOC : contenu invalide ou NULL\n");
        return (-1);
    }
    if (current->content->count > 0)
        handle_copied_heredoc(current->content, current->filename, shell);
    else
        handle_interactive_heredoc(current->filename, current->content, shell);
    return (setup_heredoc_content_pipe(current));
}


int apply_redirections(t_redir *redirs, t_minishell *shell)
{
    t_redir *current;
    int result;

    current = redirs;
    while (current)
    {
        result = 0;
        if (current->type == REDIR_IN)
        {
            // printf("DEBUG: REDIR_IN sur %s\n", current->filename);
            result = handle_redir_in(current);
        }
        else if (current->type == REDIR_HEREDOC)
        {
            // printf("DEBUG: HEREDOC avec le délimiteur : %s\n", current->filename);
            result = handle_redir_heredoc(current, shell);
        }

        if (result == -1)
            return (-1);

        current = current->next;
    }
    current = redirs;
    while (current)
    {
        result = 0;
        if (current->type == REDIR_OUT)
        {
            // printf("DEBUG: REDIR_OUT sur %s\n", current->filename);
            result = handle_redir_out(current);
        }
        else if (current->type == REDIR_APPEND)
        {
            // printf("DEBUG: REDIR_APPEND sur %s\n", current->filename);
            result = handle_redir_append(current);
        }

        if (result == -1)
            return (-1);

        current = current->next;
    }

    return (0);
}


/********************************************************* */




char	**convert_env_list(t_env_var *env_list)
{
	t_env_var	*current;
	char		**env_array;
	char		*entry;
	int			env_count;
	int			i;

	env_count = 0;
	current = env_list;
	while (current)
	{
		env_count++;
		current = current->next;
	}
	env_array = malloc(sizeof(char *) * (env_count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	current = env_list;
	while (current)
	{
		entry = ft_strjoin_free(ft_strjoin(current->key, "="), current->value, 1);
		if (!entry)
		{
			free_str_array(env_array);
			return (NULL);
		}
		env_array[i++] = entry;
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}







// execution

static int check_executable_path(char *path)
{
    struct stat path_stat;

    if (access(path, F_OK) != 0)
    {
        perror(path);
        return (127); // "No such file or directory"
    }
    if (stat(path, &path_stat) == -1)
    {
        perror(path);
        return (126); // Erreur d'accès au fichier
    }
    if (S_ISDIR(path_stat.st_mode))
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
        return (126); // Code d'erreur spécifique pour "Is a directory"
    }
    if (access(path, X_OK) != 0)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
        return (126); // Code d'erreur pour "Permission denied"
    }
    return (0); // Le chemin est valide pour exécution
}





/************************************************** */


// static int check_cmd(t_command *command)
// {
//     if (!command || !command->argv || command->argc == 0 
// 		|| ft_strlen(command->argv[0]) == 0)
// 	{
//         ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
//         return (127);
//     }
//     return (0);
// }

//no cmd
static int check_cmd(t_command *command)
{
    t_redir	*redir;

    if (!command || !command->argv || command->argc == 0 
		|| ft_strlen(command->argv[0]) == 0)
    {
        redir = command->redirs;
        while (redir)
        {
            if (redir->type == REDIR_IN)
            {
                if (access(redir->filename, F_OK) != 0)
                {
                    ft_putstr_fd("minishell: ", STDERR_FILENO);
                    perror(redir->filename); // No such file or directory
                    return (1);
                }
                return (0);
            }
            redir = redir->next;
        }
        ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
        return (127);
    }
    return (0);
}




static int execute_builtin_cmd(t_command *command, t_minishell *shell)
{
    pid_t	pid;

	if (is_builtin(command->argv[0]))
	{
		return (execute_builtin(shell, command->argv));
	}
	pid = fork();
    if (pid == 0)
	{
        if (apply_redirections(command->redirs, shell) == -1)
		{
            perror("Erreur lors de l'application des redirections");
            exit(1);
        }
        exit(execute_builtin(shell, command->argv));
    }
	else if (pid < 0)
	{
        perror("fork");
        return (1);
    }
    waitpid(pid, &shell->last_exit_status, 0);
    return (WEXITSTATUS(shell->last_exit_status));
}

// static int prepare_external_command(t_command *command, t_minishell *shell, char **path)
// {
//     *path = find_command_path(command->argv[0], shell->env_list);
//     if (!(*path)) {
//         ft_putstr_fd(command->argv[0], STDERR_FILENO);
//         ft_putstr_fd(": -commande not found-\n", STDERR_FILENO);
//         return (127);
//     }
//     return (0);
// }

static int prepare_external_command(t_command *command, t_minishell *shell, char **path)
{
    int result;

	if (ft_strcmp(command->argv[0], ".") == 0)
    {
        ft_putstr_fd("minishell: .: command not found\n", STDERR_FILENO);
        return (127);
    }
    if (ft_strchr(command->argv[0], '/'))
    {
        result = check_executable_path(command->argv[0]);
        if (result != 0)
            return (result); // "Is a directory" or "Permission denied"
        
        *path = ft_strdup(command->argv[0]);
        return (0);
    }
    *path = find_command_path(command->argv[0], shell->env_list);
    if (!(*path))
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(command->argv[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        return (127);
    }
    return (0);
}



static int process_extern(char *path, t_command *command, t_minishell *shell)
{
    pid_t	pid;

	pid = fork();
    if (pid == 0)
	{
        if (apply_redirections(command->redirs, shell) == -1)
		{
            perror("Error apply redir");
            exit(1);
        }
        execve(path, command->argv, convert_env_list(shell->env_list));
        perror("execve");
        exit(1);
    }
	else if (pid < 0)
	{
        perror("fork");
        return (1);
    }
    waitpid(pid, &shell->last_exit_status, 0);
    return (WEXITSTATUS(shell->last_exit_status));
}

static int execute_external_cmd(t_command *command, t_minishell *shell)
{
    char	*path;
    int		result;

	result = prepare_external_command(command, shell, &path);
    if (result != 0)
        return result;

    result = process_extern(path, command, shell);
    free(path);
    return (result);
}


// int execute_command(t_command *command, t_minishell *shell)
// {
//     int	result;

// 	result = check_cmd(command);
//     if (result != 0)
//         return (result);
//     if (is_builtin(command->argv[0]))
//         return (execute_builtin_cmd(command, shell));
//     return (execute_external_cmd(command, shell));
// }


int execute_command(t_command *command, t_minishell *shell)
{
    int result;

    result = check_cmd(command);
    if (result != 0 || (!command || !command->argv 
		|| command->argc == 0))
			return (result);
    if (is_builtin(command->argv[0]))
        return (execute_builtin_cmd(command, shell));
    return (execute_external_cmd(command, shell));
}




/************************************************** */

//************************PIPE*************************/

static int init_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        return (1);
    }
    return (0);
}

static pid_t fork_and_exec_left(t_ast *left, int pipefd[2], t_minishell *shell)
{
    pid_t	pid_left;

	pid_left = fork();
    if (pid_left == 0)
	{
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
            perror("dup2");
        close(pipefd[1]);
        exit(execute_ast(left, shell));
    }
	else if (pid_left < 0)
        perror("fork");
    return (pid_left);
}

static pid_t fork_and_exec_right(t_ast *right, int pipefd[2], t_minishell *shell)
{
    pid_t	pid_right;

	pid_right = fork();
    if (pid_right == 0)
	{
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
            perror("dup2");
        close(pipefd[0]);
        exit(execute_ast(right, shell));
    } 
	else if (pid_right < 0)
        perror("fork");
    return (pid_right);
}

static void close_pipe_descriptors(int pipefd[2])
{
    close(pipefd[0]);
    close(pipefd[1]);
}

static int wait_for_children(pid_t pid_left, pid_t pid_right, t_minishell *shell)
{
    int	status_left;
    int	status_right;

	status_left = 0;
	status_right = 0;
    waitpid(pid_left, &status_left, 0);
    waitpid(pid_right, &status_right, 0);
    if (WIFEXITED(status_right))
        shell->last_exit_status = WEXITSTATUS(status_right);
	else
        shell->last_exit_status = 1;
    return shell->last_exit_status;
}

int execute_pipeline(t_ast *ast, t_minishell *shell)
{
	int pipefd[2];
	pid_t pid_left;
	pid_t pid_right;

    if (!ast || ast->type != NODE_PIPE)
        return (execute_ast(ast, shell));
    if (init_pipe(pipefd) != 0)
        return (1);
    pid_left = fork_and_exec_left(ast->left, pipefd, shell);
    if (pid_left < 0)
	{
        close_pipe_descriptors(pipefd);
        return (1);
    }
    pid_right = fork_and_exec_right(ast->right, pipefd, shell);
    if (pid_right < 0)
	{
        close_pipe_descriptors(pipefd);
        return (1);
    }
    close_pipe_descriptors(pipefd);
    return (wait_for_children(pid_left, pid_right, shell));
}





/**************************************** */

// Condinionnal BONUS*******************


int execute_conditional(t_ast *ast, t_minishell *shell)
{
    if (!ast || (ast->type != NODE_AND && ast->type != NODE_OR))
    {
        fprintf(stderr, "execute_conditional: Invalid AST node type\n");
        return (1);
    }
    int left_status = execute_ast(ast->left, shell);
    if (ast->type == NODE_AND)
    {
        if (left_status == 0)
            return (execute_ast(ast->right, shell));
        else
            return left_status;
    }
    else if (ast->type == NODE_OR)
    {
        if (left_status != 0)
            return (execute_ast(ast->right, shell));
        else
            return (left_status);
    }
    fprintf(stderr, "execute_conditional: Unexpected node type\n");
    return (1);
}


/********************************************* */


/****************SUBSHELL ******************************************/

int validate_subshell_node(t_ast *ast)
{
    if (!ast || ast->type != NODE_SUBSHELL)
    {
        fprintf(stderr, "Error: Invalid node type for subshell execution.\n");
        return (0);
    }
    return (1);
}


pid_t create_subshell_process(t_ast *ast, t_minishell *shell)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }
    else if (pid == 0)
    {
        if (ast->command && ast->command->redirs)
        {
            if (apply_redirections(ast->command->redirs, shell) == -1)
            {
                perror("apply_redirections");
                exit(1);
            }
        }
        if (ast->left)
        {
            int subshell_exit = execute_ast(ast->left, shell);
            exit(subshell_exit);
        }
        exit(0);
    }
    return (pid);
}


int wait_for_subshell(pid_t pid, t_minishell *shell)
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        return (1);
    }
    if (WIFEXITED(status))
        shell->last_exit_status = WEXITSTATUS(status);
    else
        shell->last_exit_status = 1;
    return (shell->last_exit_status);
}



int execute_subshell(t_ast *ast, t_minishell *shell)
{
    pid_t pid;

    if (!validate_subshell_node(ast))
        return (1);

    pid = create_subshell_process(ast, shell);
    if (pid == -1)
        return (1);
    return (wait_for_subshell(pid, shell));
}








/********************************************* */


// Parcourir l'AST
int	execute_ast(t_ast *ast, t_minishell *shell)
{
	if (!ast)
		return (1);
	if (ast->type == NODE_COMMAND)
	{
    	shell->nb_line_heredoc++;
		return (execute_command(ast->command, shell));
	}	
	else if (ast->type == NODE_PIPE)
		return (execute_pipeline(ast, shell));
	else if (ast->type == NODE_AND || ast->type == NODE_OR)
		return (execute_conditional(ast, shell));
	else if (ast->type == NODE_SUBSHELL)
		return (execute_subshell(ast, shell));
	else
		ft_putstr_fd("Erreur : Type de nœud AST inconnu\n", 2);
	return (1);
}



































































// gcc -Wall -Wextra etape1.c libft.a -lreadline
// gcc -g -Wall -Wextra etape1.c libft.a -lreadline
// valgrind --leak-check=full ./a.out


// etape 1 : normalisation

char *prompt_input(char *prompt)
{
	char	*input = NULL;

	if (!prompt)
		return (NULL);
	input = readline(prompt);
	if (!input)
	{
		write(1, "exit\n", 5); // Gestion Ctrl+D
		return (NULL);
	}
	if (input && *input) 
		add_history(input);
	return (input);
}


// void init_minishell(t_minishell *shell)
// {
//     shell.env_list = env_list;
// 	shell.last_exit_status = 0;
// 	shell.tokens = NULL;
// 	shell.ast = NULL;
// 	shell.running = 1;
// 	shell.fd_input = STDIN_FILENO;
// 	shell.fd_output = STDOUT_FILENO;
//     shell->heredoc_line_nb = 1;
// }


void minishell_loop(t_env_var *env_list)
{
    char    *prompt = NULL;
    char    *input = NULL;
    t_token *token_list = NULL;
    t_ast   *ast_root = NULL;
	t_minishell shell;

// init shell
shell.env_list = env_list;
shell.last_exit_status = 0;
shell.tokens = NULL;
shell.ast = NULL;
shell.running = 1;
shell.fd_input = STDIN_FILENO;
shell.fd_output = STDOUT_FILENO;
shell.nb_line_heredoc = 0;

    while (1)
    {
        // 1)
        prompt = format_prompt();
        if (!prompt)
        {
            ft_putstr_fd("minishell: Error creating prompt\n", 2);
            break;
        }

        // 2)
        input = prompt_input(prompt);
        free(prompt);

        //ctrl+D
        if (!input)
            break;

    //    3)
        token_list = lexer(input);
        if (!token_list)
        {
            free(input);
            continue;
        }
		printf("------>>>> TOKEN:\n");
		print_tokens(token_list);


		// 4)

		expand_token_list(token_list, &shell);

		printf("------>>>> expander:\n");
		print_tokens(token_list);

		



    //  5)
        ast_root = parse(token_list, input);

        free_token_list(token_list);
        token_list = NULL;

        if (!ast_root)
        {
            free(input);
            continue;
        }
		printf("------>>>> Parser:\n");
		print_ast(ast_root, 0);
       
     
    //  6)

		printf("\n------------execution---------\n");
        execute_ast(ast_root, &shell);

        free_ast(ast_root);
        ast_root = NULL;

        free(input);
        input = NULL;
    }
}			







int main(int argc, char **argv, char **envp)
{
    t_env_var *env_list = NULL; 

    check_args(argc, argv);

    env_list = convert_envp_to_list(envp);
    if (!env_list)
    {
        ft_putstr_fd("minishell: Failed to initialize environment\n", 2);
        return (1);
    }

    main_signals();

	// printf("*****************ENV********************\n");
	// print_env_list(env_list);
	// printf("*****************ENV********************\n");

    minishell_loop(env_list);

    free_env_list(env_list);
    rl_clear_history();

    return (0);
}
