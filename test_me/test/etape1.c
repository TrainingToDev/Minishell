
#include "min.h"

// Gestion de l'argument du programme
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
// Gestion de prompt
char	*get_default_prompt()
{
	char	*cwd;
	char	*prompt;
	char	*tmp;
	char	*path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("minishell$:");
	if (!cwd)
		return (NULL);
	tmp = ft_strjoin("\001"COLOR_GREEN"\002", "minishell:");
	path = ft_strjoin("\001"COLOR_BLUE"\002", cwd);
	free(cwd);
	if (!tmp || !path)
	{
		free(tmp);
		free(path);
		return (NULL);
	}
	prompt = ft_strjoin(tmp, path);
	free(tmp);
	free(path);
	if (!prompt)
		return (NULL);
	tmp = prompt;
	prompt = ft_strjoin(prompt, "\001"COLOR_RESET"\002$ ");
	free(tmp);
	return (prompt);
}


void    free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
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

	 // erreurs de syntaxe
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

void	handle_eof(void)
{
	ft_putstr_fd("Exiting minishell. Goodbye!\n", 1);
	exit(EXIT_SUCCESS);
}



void    display_error(const char *message)
{
	if (!message)
		return ;
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, "\n", 1);
}


// lexer


t_token *create_token(t_token_type type, const char *value, int expand)
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
		display_error("Memory allocation error");
		return (NULL);
	}
	new_token->type = type;
	new_token->expand = expand;
	new_token->next = NULL;
	return (new_token);
}


void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return ;
	if (new_token->next)
	{
		display_error("Token already linked");
        return ;
	}
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}


int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}



t_token_type get_op_token(const char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0) //for bonus
		return (TOKEN_AND);
	else if (ft_strncmp(str, "||", 2) == 0) //for bonus
		return (TOKEN_OR);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (*str == '>')
		return (TOKEN_REDIRECT_OUT);
	else if (*str == '<')
		return (TOKEN_REDIRECT_IN);
	else if (*str == '|')
		return (TOKEN_PIPE);
	else if (*str == '(') // for bonus
		return (TOKEN_LPAREN);
	else if (*str == ')') // for bonus
		return (TOKEN_RPAREN);
	else
		return (TOKEN_UNKNOWN); // Cas d'erreur
}


int	is_operator(const char *str)
{
	if (!str)
		return (0);
	if ((str[0] && str[1]) && (ft_strncmp(str, "&&", 2) == 0 
		|| ft_strncmp(str, "||", 2) == 0 || ft_strncmp(str, ">>", 2) == 0 
			|| ft_strncmp(str, "<<", 2) == 0))
		return (2);
	else if (*str == '|' || *str == '>' || *str == '<' ||
			 *str == '(' || *str == ')')
		return (1);
	else
		return (0);
}

//* manage operator */

static char *extract_operator_value(char *input, size_t *i, int *op_len)
{
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
        return;
    new_token = create_token(get_op_token(&input[*i]), value, 0);
    free(value);
    if (!new_token)
        return;
    add_token(tokens, new_token);
    *i += op_len;
}
//**** */




//manage quote
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
char	*join_and_free(char *value, char *part)
{
    char	*tmp;

	tmp = ft_strjoin(value, part);
    free(value);
    free(part);
    if (!tmp)
        print_error(E_NOMEM, NULL, 11);
    return (tmp);
}

char	*extract_part(char *input, size_t *i)
{
    size_t	start;

	start = *i;
    while (input[*i] && !ft_isspace(input[*i])
			&& !is_operator(&input[*i])
				&& !is_quote(input[*i]))
        			(*i)++;
    return (ft_substr(input, start, *i - start));
}

char	*quoted_part(char *input, size_t *i, int *expand, char *value)
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

char	*process_input(char *input, size_t *i, int *expand, char *value)
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


char	*extract_word_value(char *input, size_t *i, int *expand)
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
		free(value);
	return (value);
}
/******* */

// tokenisation
void add_word_token(t_token **tokens, char *input, size_t *i)
{
	char	*value;
	t_token	*new_token;
	int		expand;

	if (!tokens)
		return ;
	expand = 0;
	value = extract_word_value(input, i, &expand);
	if (!value)
	{
		free_token_list(*tokens);
		return ;
	}
	new_token = create_token(TOKEN_WORD, value, expand);
	printf("1- value=%p - value=%s\n", value, value);
	printf("2- new_token=%p - token=%s\n", new_token, new_token->value);
	free(value);
	value = NULL;
	printf("1- value=%p - value=%s\n", value, value);
	printf("2- new_token=%p - token=%s\n", new_token, new_token->value);
	if (!new_token)
	{
		print_error(E_NOMEM, NULL, 11);
		free_token_list(*tokens);
		exit(EXIT_FAILURE);
	}
	add_token(tokens, new_token);
}





// error lexer

// step 1
// not manage

int validate_input(char *input)
{
    size_t i;
	size_t j;

    if (!input || *input == '\0')
        return (0);
    if (ft_strchr("~%^&(){}[|", input[0]))
    {
        print_error(E_SYNTAX, &input[0], 10);
        return (-1);
    }
    i = 0;
    while (input[i])
    {
        if (input[i] == '\\' && input[i + 1] == '\0')
        {
            print_error(E_SYNTAX, "\\", 10);
            return (-1);
        }
        if (input[0] == '#')
        return (-1); // 
        if (input[i] == '!' && (i == 0 || ft_isspace(input[i - 1])))
        {
            j = i + 1;
            while (input[j] && ft_isspace(input[j]))
                j++;
            if (input[j] == '\0') 
            {
                print_error(E_SYNTAX, "!", 10);
                return (-1);
            }
        }
        i++;
    }
    return (0); 
}


int validate_syntax(t_token *tokens)
{
    t_token *current = tokens;
    t_token *prev = NULL;

    while (current)
    {
        if (current->type == TOKEN_PIPE)
        {
            if (!prev || !current->next || prev->type == TOKEN_PIPE 
				|| prev->type == TOKEN_AND || prev->type == TOKEN_OR)
            {
                print_error(E_SYNTAX, "|", 10);
                return (-1);
            }
        }

        if (current->type == TOKEN_REDIRECT_IN || current->type == TOKEN_REDIRECT_OUT 
			|| current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC)
        {
            if (!current->next || current->next->type != TOKEN_WORD)
            {
                print_error(E_SYNTAX, current->value, 10);
                return (-1);
            }
        }

        if (current->type == TOKEN_AND || current->type == TOKEN_OR)
        {
            if (!prev || !current->next || prev->type == TOKEN_AND || prev->type == TOKEN_OR)
            {
                print_error(E_SYNTAX, current->value, 10);
                return (-1);
            }
        }

        if (current->type == TOKEN_LPAREN)
        {
            if (!current->next || (current->next->type == TOKEN_RPAREN))
            {
                print_error(E_SYNTAX, "(", 10);
                return (-1);
            }
        }
        if (current->type == TOKEN_RPAREN)
        {
            if (!prev || prev->type == TOKEN_PIPE || prev->type == TOKEN_AND 
				|| prev->type == TOKEN_OR)
            {
                print_error(E_SYNTAX, ")", 10);
                return (-1);
            }
        }

        prev = current;
        current = current->next;
    }

    if (prev && (prev->type == TOKEN_PIPE || prev->type == TOKEN_AND 
		|| prev->type == TOKEN_OR))
    {
        print_error(E_SYNTAX, prev->value, 258);
        return (-1);
    }

    return (0);
}






















//******************************* */
int check_tokens(t_token *tokens)
{
	if (!tokens)
	{
		return (0);
	}
	return (1);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	size_t	i;

	if (!input)
		return (NULL);
	
	tokens = NULL;

//step 1: validation syntax
	if (validate_input(input) == -1)
        return (NULL);


//step 2: lexing
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		if (ft_isspace(input[i]))
			i++;
		else if (is_operator(&input[i]))
		{	
			add_operator_token(&tokens, input, &i);
		}
		else
		{
			add_word_token(&tokens, input, &i);
		}	
	}

//step 3: validation syntax
	if (validate_syntax(tokens) == -1)
    {
        free_token_list(tokens);
        return (NULL);
    }
	if (!check_tokens(tokens))
	{
		free_token(tokens);
		return (NULL);
	}

	return (tokens);
}


//content heredoc


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

void free_heredoc_content(t_heredoc_content *content)
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

void	print_heredoc_content(const t_heredoc_content *content)
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

t_heredoc_content	*init_heredoc(void)
{
	t_heredoc_content	*content;

	content = malloc(sizeof(t_heredoc_content));
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

int	add_line(t_heredoc_content *content, const char *line)
{
	char	**new_lines;
	size_t	j;
	size_t	k;

	new_lines = malloc(sizeof(char *) * (content->count + 1));
	if (!new_lines)
		return (-1);
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
		while (k < content->count)
		{
			free(new_lines);
			k++;
		}
		return (-1);
	}
	content->lines = new_lines;
	content->count++;
	return (0);
}

int	get_lines(t_heredoc_content *content, char **lines, const char *delimiter)
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
		if (ft_strcmp(lines[i], delimiter) == 0)
			return (0);
		i++;
	}
	return (0);
}


t_heredoc_content	*get_heredoc_lines(const char *input, const char *delimiter)
{
	t_heredoc_content	*content;
	char				**lines;

	if (!input || !delimiter)
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
	if (get_lines(content, lines, delimiter) == -1)
	{
		free_heredoc_content(content);
		free_split(lines);
		return (NULL);
	}
	free_split(lines);
	return (content);
}


void	process_heredoc(const t_token *tokens, const char *input)
{
	const t_token		*current;
	t_heredoc_content	*content;
	char				*delimiter;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (current->next)
				delimiter = current->next->value;
			else
				delimiter = NULL;
			if (delimiter)
			{
				printf("Handling heredoc with delimiter: %s\n", delimiter);
				content = get_heredoc_lines(input, delimiter);
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




const char *get_token_type_name(t_token_type type)
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



void	print_tokens(t_token *tokens)
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
//parser

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_redirections(t_redirection *redirs)
{
	t_redirection	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		free(tmp->filename);
		free(tmp);
	}
}


void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	free_string_array(cmd->argv);
	free_redirections(cmd->redirs);
	free(cmd);
}


void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == NODE_COMMAND)
		free_command(ast->command);
	else
	{
		free_ast(ast->left);
		free_ast(ast->right);
	}
	free(ast);
}






t_ast	*create_ast_node(t_node_type type, t_command *cmd)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		display_error("Memory allocation failed for AST node");
		return	(NULL);
	}
	node->type = type;
	node->command = cmd;
	node->operator = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast   *create_pipe_node(t_ast *left, t_ast *right)
{
    t_ast	*node;

	node = create_ast_node(NODE_PIPE, NULL);
    if (!node)
        return (NULL);
    node->left = left;
    node->right = right;
    return (node);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		display_error("Memory allocation failed for t_command");
		return (NULL);
	}
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->redirs = NULL;
	return (cmd);
}


t_redirection	*init_redir(t_token_type type)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	if (type == TOKEN_REDIRECT_IN)
		redir->type = REDIR_IN;
	else if (type == TOKEN_REDIRECT_OUT)
		redir->type = REDIR_OUT;
	else if (type == TOKEN_APPEND)
		redir->type = REDIR_APPEND;
	else if (type == TOKEN_HEREDOC)
		redir->type = REDIR_HEREDOC;
	return (redir);
}

void	add_redir(t_redirection **current, t_redirection *redir)
{
	while (*current)
		current = &((*current)->next);
	*current = redir;
	redir->next = NULL;
}

int add_redirection(t_redirection **redirs, t_token *token)
{
	t_redirection	*redir;

    if (!token || !token->next || token->next->type != TOKEN_WORD)
    {
        print_error(E_SYNTAX, token->value, 10);
        return (0);
    }
    redir = init_redir(token->type);
    if (!redir)
    {
        print_error(E_NOMEM, NULL, 11);
        return (0);
    }
    redir->filename = ft_strdup(token->next->value);
    if (!redir->filename)
    {
        free(redir);
        print_error(E_NOMEM, NULL, 11);
        return (0);
    }
    add_redir(redirs, redir);
    return (1);
}









t_ast *parse_command(t_token **tokens)
{
	t_command		*command ;
	t_redirection	*redir;
	t_ast			*node;

    if (!tokens || !*tokens)
        return (NULL);

    command = init_command();
    if (!command)
        return (NULL);

    // arg
    while (*tokens && (*tokens)->type == TOKEN_WORD)
    {
        char **new_argv = realloc(command->argv, sizeof(char *) * (command->argc + 2));
        if (!new_argv)
        {
            free_command(command);
            print_error(E_NOMEM, NULL, 11);
            return (NULL);
        }

        command->argv = new_argv;
        command->argv[command->argc] = ft_strdup((*tokens)->value);
        command->argv[++command->argc] = NULL;

        *tokens = (*tokens)->next;
    }

    //redir
    while (*tokens && ((*tokens)->type >= TOKEN_REDIRECT_IN && (*tokens)->type <= TOKEN_HEREDOC))
    {
        
	
		redir = init_redir((*tokens)->type);
        if (!redir)
        {
            free_command(command);
            print_error(E_NOMEM, NULL, 11);
            return (NULL);
        }

        if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
        {
            free(redir);
            free_command(command);
            print_error(E_SYNTAX, (*tokens)->value, 10);
            return (NULL);
        }

        redir->filename = ft_strdup((*tokens)->next->value);
        if (!redir->filename)
        {
            free(redir);
            free_command(command);
            print_error(E_NOMEM, NULL, 11);
            return (NULL);
        }

        add_redir(&command->redirs, redir);

        *tokens = (*tokens)->next->next;
    }

	node = create_ast_node(NODE_COMMAND, command);
    if (!node)
    {
        free_command(command);
        print_error(E_NOMEM, NULL, 11);
        return (NULL);
    }

    return (node);
}

t_ast *parse_pipeline(t_token **tokens)
{
    t_ast *left;
	t_ast *right;

	left = parse_command(tokens);
    if (!left)
        return (NULL);

    while (*tokens && (*tokens)->type == TOKEN_PIPE)
    {
        *tokens = (*tokens)->next; // Consommer token `|`
        
		right = parse_command(tokens);
        if (!right)
        {
            free_ast(left);
            print_error(E_SYNTAX, "|", 10);
            return (NULL);
        }

        left = create_pipe_node(left, right);
        if (!left)
        {
            free_ast(right);
            return (NULL);
        }
    }

    return left;
}




t_ast *parse_subshell(t_token **tokens)
{
	t_ast	*subshell;

    if (!tokens || !*tokens || (*tokens)->type != TOKEN_LPAREN)
        return (NULL);

    *tokens = (*tokens)->next; // Consommer '('
	subshell = parse_pipeline(tokens);
    if (!subshell || !*tokens || (*tokens)->type != TOKEN_RPAREN)
    {
        free_ast(subshell);
        print_error(E_SYNTAX, ")", 10);
        return (NULL);
    }

    *tokens = (*tokens)->next; // Consommer ')'

    return create_ast_node(NODE_SUBSHELL, NULL); // Create node type subshell
}




t_ast *parse_tokens(t_token **tokens)
{
	 t_ast *ast;

	if (!tokens || !*tokens)
		return (NULL);
	ast = parse_pipeline(tokens);
	if (!ast)
		print_error(E_SYNTAX, "Invalid syntax", 10);
    return (ast);
}


//logical cmd implementation

void    print_ast(t_ast *ast, int depth)
{
	int i;
	t_redirection *redir;

	if (!ast)
		return;
	i = 0;
	while(i < depth)
	{
		printf("  ");
		i++;
	}
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
	if (ast->type == NODE_COMMAND && ast->command)
	{
		printf("[ ");
		int i = 0;
		while ( i < ast->command->argc)
		{
			printf("%s ", ast->command->argv[i]);
			i++;
		}
		printf("]\n");
		redir = ast->command->redirs;
		while (redir)
		{
			int i = 0;
			while ( i < depth + 1)
			{
				printf("  ");
				i++;
			}
			if (redir->type == REDIR_IN)
				printf("REDIR_IN: %s\n", redir->filename);
			else if (redir->type == REDIR_OUT)
				printf("REDIR_OUT: %s\n", redir->filename);
			else if (redir->type == REDIR_APPEND)
				printf("REDIR_APPEND: %s\n", redir->filename);
			else if (redir->type == REDIR_HEREDOC)
				printf("REDIR_HEREDOC: %s\n", redir->filename);
			redir = redir->next;
		}
	}
	else
		printf("\n");
	print_ast(ast->left, depth + 1);
	print_ast(ast->right, depth + 1);
}























// gcc -Wall -Wextra etape1.c ../libft/libft.a -lreadline
// gcc -g -Wall -Wextra etape1.c ../libft/libft.a -lreadline
// valgrind --leak-check=full ./a.out

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	t_token	*tokens;
	t_ast	*ast;

	(void)envp;
	check_args(argc, argv);
	setup_signal();

	prompt = get_default_prompt();
	if (!prompt)
	{
		ft_putstr_fd(COLOR_RED "Error: Failed to allocate prompt.\n" COLOR_RESET, 2);
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		input = readline(prompt);
		if (!input) // Gestion de CTRL-D(EOF)
		{
			free (prompt);
			
			handle_eof();
		}
		if (*input)
			add_history(input);

		// Token && parsing
		tokens = lexer(input);
		if(!tokens)
		{
			status_manager(258, STATUS_WRITE);
				free_token_list(tokens);
			free(input);
			continue;
		}
		print_tokens(tokens);
		process_heredoc(tokens, input);


		ast = parse_tokens(&tokens);
		// free_token_list(tokens);
		if (!ast)
		{
			printf("Parser error: Unable to create AST.\n");
			free_ast(ast);
			free_token_list(tokens);
			free(input);
			continue;
		}
		printf("Abstract Syntax Tree (AST):\n");
		free_token(tokens);
		tokens = NULL;

		print_ast(ast, 0);

		printf("ast: %p\n", ast->command->argv);
		printf("ast: %p\n", ast->command->argv);
		free_ast(ast);
		ast = NULL;
		printf("ast: %p\n", ast);
		printf("ast: %p\n", ast);
		
		free(input);
	}

	free(prompt);
	// rl_clear_history();
	return (0);
}



