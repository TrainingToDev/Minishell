/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etape1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:21:30 by herandri          #+#    #+#             */
/*   Updated: 2024/12/21 14:03:54 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"

// step 1

// manage args program
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

// imitation to bash prompt
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

//free token

void    free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
	{
		printf("LOG: Freeing token value: %s\n", token->value);
		free(token->value);
	}
	free(token);
}

void	free_token_list(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		printf("LOG: Freeing token with value: %s\n", tokens->value);
		
		free_token(tokens);
		tokens = tmp;
		printf("LOG: All tokens freed.\n"); // LOG: Fin de la liste
	}
}

// void free_token_list (t_token **tokens)
// {
//     t_token *current;
//     t_token *tmp;

//     current = *tokens;
//     while (current)
//     {
//         tmp = current->next;
//         free(current->value);
//         free(current);
//         current = tmp;
//     }
//     *tokens = NULL;
// }




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
	return (status);
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



// error msg

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
void	manage_signal(int sig)
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

void	setup_signals(void)
{
	signal(SIGINT, manage_signal); //CTRL+C
	signal(SIGQUIT, SIG_IGN); // ctrl+'\'
}


// function not use
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



// need amelioration
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
		printf("LOG: new_token added as the first token in the list!!!\n");
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
	
	printf("LOG: new_token added to the end of the list at %p\n", (void *)current->next);
}

// check_qoute
int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

// check type of token
t_token_type get_op_token(const char *str)
{
	if (ft_strncmp(str, ">|", 2) == 0)
		return (TOKEN_REDIRECT_OUT); // type force overwrite
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

// check operator
int	is_operator(const char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, ">|", 2) == 0)
		return (2);
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

// manage operator
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

// add operator to tokens
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


/**** check word value ****/
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
	char	*part;
	char	*tmp;
	int		part_expand;

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
/********************************************************************/

// tokenisation
void add_word_token(t_token **tokens, char *input, size_t *i)
{
	char        *value;
	t_token     *new_token;
	int         expand;

	if (!tokens)
	{
		 printf("LOG: tokens pointer is NULL\n");
		 return ;
	}
	expand = 0;
	value = extract_word_value(input, i, &expand);
	if (!value)
	{
		printf("LOG: extract_word_value returned NULL. Freeing tokens...\n");
		free_token_list(*tokens);
		*tokens = NULL;
		return ;
	}
	printf("LOG: Extracted word value: [%s]\n", value);
	new_token = create_token(TOKEN_WORD, value, expand);
	free(value);
	if (!new_token)
	{
		 printf("LOG: create_token failed. Freeing tokens...\n");
		free_token_list(*tokens);
		*tokens = NULL;
		return ;
	}
	printf("LOG: ALLOCATED new_token at %p, value: [%s], expand: %d\n", (void *)new_token, new_token->value, new_token->expand);

	add_token(tokens, new_token);
}

// redirection not supported!!!
int is_unsup_simple_redir(const char *input)
{
	if (ft_strncmp(input, "2>", 2) == 0 || ft_strncmp(input, "2>>", 3) == 0
		|| ft_strncmp(input, ">&", 2) == 0 || ft_strncmp(input, "&>", 2) == 0 
		|| ft_strncmp(input, "&>>", 3) == 0 || ft_strncmp(input, "<<<", 3) == 0)
	{
		print_error(E_SYNTAX, "Unsupported redirection", 2);
		return (1);
	}
	return (0);
}

int is_unsup_output_redir(const char *input)
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

int is_unsup_input_redir(const char *input)
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


int is_unsup_descriptor_redir(const char *input)
{
	if (is_unsup_output_redir(input)) // Vérifie les redirections de sortie
		return (1);
	if (is_unsup_input_redir(input)) // Vérifie les redirections d'entrée
		return (1);
	return (0); // Pas de redirection non supportée
}

t_token_type invalid_redir(const char *input)
{
	if (is_unsup_simple_redir(input)) // Cas simples comme `>&`, `&>`, `<<<`
		return (TOKEN_UNKNOWN);
	if (is_unsup_descriptor_redir(input)) // Cas avances comme `n>&m`, `n<&m`, etc.
		return (TOKEN_UNKNOWN);
	return (TOKEN_WORD);
}

// validation
int check_tokens_validity(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_UNKNOWN)
		{
			print_error(E_SYNTAX, tokens->value, 2);
			return (0); // Token invalide detected
		}
		tokens = tokens->next;
	}
	return (1);
}

int is_operator_invalid_prev(t_token *prev, t_token *current) 
{
	if (!prev || prev->type == TOKEN_PIPE || prev->type == TOKEN_AND 
		|| prev->type == TOKEN_OR || prev->type == TOKEN_LPAREN)
	{
		print_error(E_SYNTAX, current->value, 2);
		return (1);
	}
	return (0);
}

int is_operator_invalid_next(t_token *current) 
{
	if (!current->next || current->next->type == TOKEN_PIPE || 
		current->next->type == TOKEN_AND || current->next->type == TOKEN_OR
		|| current->next->type == TOKEN_RPAREN)
	{
		print_error(E_SYNTAX, current->value, 2);
		return (1);
	}
	return (0);
}


int check_operators(t_token *tokens) 
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_AND 
			|| tokens->type == TOKEN_OR)
		{
			if (is_operator_invalid_prev(prev, tokens)) 
				return (0);
			if (is_operator_invalid_next(tokens)) 
				return (0);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}


//redir
int valid_general_redir(t_token *token)
{
	if (!token->next) // Vérifie si le token suivant existe
	{
		print_error(E_SYNTAX, "newline", 2);
		return (0);
	}
	if (token->type == TOKEN_REDIRECT_OUT && token->next->type == TOKEN_PIPE)
	{
		print_error(E_SYNTAX, "|", 2); // Erreur spécifique pour `|`
		return (0);
	}
	if (token->next->type != TOKEN_WORD && token->next->type != TOKEN_PIPE)
	{
		print_error(E_SYNTAX, token->next->value, 2);
		return (0);
	}
	return (1);
}

// validation >|
int validate_force_overwrite(t_token *token)
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

int check_redirections(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_REDIRECT_OUT || tokens->type == TOKEN_APPEND
			|| tokens->type == TOKEN_REDIRECT_IN || tokens->type == TOKEN_HEREDOC)
		{
			// Cas général
			if (!valid_general_redir(tokens))
				return (0);

			// Cas spécifique pour `>|`
			if (tokens->type == TOKEN_REDIRECT_OUT 
				&& !validate_force_overwrite(tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}



//bonus
int check_parentheses(t_token *tokens)
{
	int count = 0;

	while (tokens)
	{
		if (tokens->type == TOKEN_LPAREN)
			count++;
		else if (tokens->type == TOKEN_RPAREN)
		{
			count--;
			if (count < 0)
			{
				print_error(E_SYNTAX, tokens->value, 258);
				return (0); // braket not match
			}
		}
		tokens = tokens->next;
	}
	if (count != 0)
	{
		print_error(E_SYNTAX, "unmatched parenthesis", 258);
		return (0);
	}
	return (1);
}


int validate_syntax(t_token *tokens)
{
	if (!tokens)
		return (0); // not token for validation

	if (!check_operators(tokens))
		return (0); // Error in operator

	if (!check_redirections(tokens))
		return (0); // Error in redirection
	if (!check_parentheses(tokens))
		return (0); // Error in brackets

	if (!check_tokens_validity(tokens))
		return (0); // Token invalide detected

	return (1); // Syntaxe valide
}


// step 2
//******************************* */
//lexer

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	size_t	i;

	if (!input)
		return (NULL);
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

int validate_tokens(t_token *tokens)
{
	if (!validate_syntax(tokens))
		return (0);
	if (!tokens)
		return (0);
	return (1);
}

t_token *lexer(char *input)
{
	t_token	*tokens;

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


//manage content heredoc
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

// function utils to parsing
int	get_lines(t_hdc *content, char **lines, const char *delimiter)
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

// get content heredocs copy-paster
t_hdc	*get_heredoc_lines(const char *input, const char *delimiter)
{
	t_hdc	*content;
	char	**lines;

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

//print heredoc
void	process_heredoc(const t_token *tokens, const char *input)
{
	const t_token		*current;
	t_hdc	*content;
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



// use to print token
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


// print token
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



// Expander




// add implementation expanding



/* ********************************************* */

// step 3

//free for parsing

void free_command(t_command *cmd)
{
	t_redir *redir;
	t_redir *next;
	int i;

	if (!cmd)
		return;
	// free args
	i = 0;
	while (i < cmd->argc)
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	// Libération des redirections
	redir = cmd->redirs;
	while (redir)
	{
		next = redir->next;
		free(redir->filename);

		// free content heredoc
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


// init

// Initialize a new AST node
t_ast	*create_ast_node(t_node_type type, t_command *cmd)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		print_error(E_NOMEM, "Failed to allocate memory for command", 11);
		return	(NULL);
	}
	node->type = type;
	node->command = cmd;
	node->operator = TOKEN_UNKNOWN;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// Initialize a new command structure
t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		print_error(E_NOMEM, "Failed to allocate memory", 11);
		return (NULL);
	}
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->redirs = NULL;
	return (cmd);
}

// create pipe
t_ast   *create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = create_ast_node(NODE_PIPE, NULL);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	
	if (!left || !right)
		print_error(E_NOMEM, "Warning: NULL", 11);
	return (node);
}

// cmd manage logical
t_ast	*create_logical_node(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = create_ast_node(type, NULL);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}

// init redir
t_redir	*init_redir(t_token_type type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
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
	redir->filename = NULL;
	redir->content = NULL;
	redir->next = NULL;
	return (redir);
}

//parser

// add redir
void	add_redir(t_redir **current, t_redir *redir)
{
	while (*current)
		current = &((*current)->next);
	*current = redir;
}

//manage
int validate_redir_tokens(t_redir **redirs, t_token **tokens)
{
	t_redir *redir;

	if (!tokens || !*tokens)
		return (0);
	redir = init_redir((*tokens)->type);
	if (!redir)
		return (0);
	*redirs = redir;
	return (1);
}

// manage content heredocs
int process_heredoc_redir(t_redir *redir, t_token **tokens, const char *input)
{
	if (redir->type == REDIR_HEREDOC)
	{
		redir->content = get_heredoc_lines(input, (*tokens)->value);
		if (!redir->content)
		{
			free(redir);
			print_error(E_SYNTAX, "Failed to process heredoc", 1);
			return (0);
		}
	}
	return (1);
}

int finalize_redir(t_redir *redir, t_redir **redirs, t_token **tokens)
{
	t_token *current;

	redir->filename = ft_strdup((*tokens)->value);
	if (!redir->filename)
	{
		free(redir);
		print_error(E_NOMEM, "Memory allocation failed for filename", 11);
		return (0);
	}

	add_redir(redirs, redir);

	// filename consom
	current = *tokens;
	*tokens = (*tokens)->next;
	free_token(current);

	return (1);
}

int handle_redirection(t_redir **redirs, t_token **tokens, const char *input)
{
	t_redir *redir;
	t_token *current;

	if (!validate_redir_tokens(&redir, tokens))
		return (0);
	// redir consom
	current = *tokens;
	*tokens = (*tokens)->next;
	free_token(current);

	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		free(redir);
		print_error(E_SYNTAX, "Invalid redirection syntax", 1);
		return (0);
	}
	if (!process_heredoc_redir(redir, tokens, input))
		return (0);
	if (!finalize_redir(redir, redirs, tokens))
		return (0);

	return (1);
}



// add args cmd

int allocate_and_copy_argv(t_command *command, char ***new_argv)
{
	int i;

	*new_argv = malloc(sizeof(char *) * (command->argc + 2));
	if (!*new_argv)
	{
		print_error(E_NOMEM, "Failed to allocate memory for argv", 11);
		return (0);
	}
	i = 0;
	while (i < command->argc)
	{
		(*new_argv)[i] = command->argv[i];
		i++;
	}
	(*new_argv)[command->argc] = NULL;
	return (1);
}


int add_argument_to_argv(t_command *command, char *value, char **new_argv)
{
	command->argv = new_argv;
	command->argv[command->argc] = ft_strdup(value);
	if (!command->argv[command->argc])
	{
		print_error(E_NOMEM, "Failed to allocate memory for argument", 11);
		for (int i = 0; i < command->argc; i++)
			free(command->argv[i]);
		free(command->argv);
		command->argv = NULL;
		return (0);
	}

	command->argv[++command->argc] = NULL;
	return (1);
}


int parse_args(t_command *command, t_token **tokens)
{
	char **new_argv;
	t_token *current;

	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		if (!allocate_and_copy_argv(command, &new_argv))
			return (0);

		free(command->argv);

		if (!add_argument_to_argv(command, (*tokens)->value, new_argv))
			return (0);

		current = *tokens;
		*tokens = (*tokens)->next;
		free_token(current);
	}
	return (1);
}

//end

// find token redirection
int is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN
			|| type == TOKEN_REDIRECT_OUT
				|| type == TOKEN_APPEND 
					|| type == TOKEN_HEREDOC);
}

//parse and consom 
t_ast *parse_inner_subshell(t_token **tokens, const char *input)
{
	t_ast *inner_ast;
	t_token *current;

	if (!tokens || !*tokens || (*tokens)->type != TOKEN_LPAREN)
		return (NULL);

	current = *tokens;
	*tokens = (*tokens)->next;
	free_token(current);

	inner_ast = parse_logical_expression(tokens, input);
	if (!inner_ast || !*tokens || (*tokens)->type != TOKEN_RPAREN)
	{
		free_ast(inner_ast);
		print_error(E_SYNTAX, "Expected closing parenthesis ')'", 1);
		return (NULL);
	}
	// Consommer ')'
	current = *tokens;
	*tokens = (*tokens)->next;
	free_token(current);
	return (inner_ast);
}

// for bonus: manage subshell
t_ast *parse_subshell(t_token **tokens, const char *input)
{
	t_ast *inner_ast;
	t_ast *subshell_node;

	inner_ast = parse_inner_subshell(tokens, input);
	if (!inner_ast)
		return (NULL);

	subshell_node = create_ast_node(NODE_SUBSHELL, NULL);
	if (!subshell_node)
	{
		free_ast(inner_ast);
		print_error(E_NOMEM, "Failed to allocate subshell node", 11);
		return (NULL);
	}
	subshell_node->left = inner_ast;
	return (subshell_node);
}


// Init data for cmd
t_command *init_command_data()
{
	t_command *cmd;

	cmd = init_command();
	if (!cmd)
	{
		print_error(E_NOMEM, "Failed to allocate memory for command data", 11);
		return (NULL);
	}
	return (cmd);
}

// manage redir and cmd for only cmd
int process_command_details(t_command *cmd, t_token **tokens, const char *input)
{
	while (*tokens)
	{
		if (is_redir_token((*tokens)->type))
		{
			if (!handle_redirection(&cmd->redirs, tokens, input))
				return (0);
		}
		else if ((*tokens)->type == TOKEN_WORD)
		{
			if (!parse_args(cmd, tokens))
				return (0);
		}
		else
			break;
	}
	return (1);
}

// manage cmd and sus
t_ast *parse_command(t_token **tokens, const char *input)
{
	t_command *cmd;
	t_ast *node;

	if ((*tokens)->type == TOKEN_LPAREN)
		return parse_subshell(tokens, input);

	cmd = init_command_data(tokens);
	if (!cmd)
		return (NULL);

	if (!process_command_details(cmd, tokens, input))
	{
		free_command(cmd);
		return (NULL);
	}
	node = create_ast_node(NODE_COMMAND, cmd);
	if (!node)
	{
		free_command(cmd);
		print_error(E_NOMEM, NULL, 11);
		return (NULL);
	}
	return (node);
}

t_ast *handle_pipeline_(t_token **tokens, const char *input, t_ast *left)
{
	t_token *current;
	t_ast *right;

	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		current = *tokens;
		*tokens = (*tokens)->next; // Consommer token `|`
		free_token(current);

		right = parse_command(tokens, input);
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
	return (left);
}


t_ast *parse_pipeline(t_token **tokens, const char *input)
{
	t_ast *left;

	left = parse_command(tokens, input);
	if (!left)
		return (NULL);
	return (handle_pipeline_(tokens, input, left));
}


// pipe
t_ast *update_logical_node(t_ast *left, t_ast *right, t_token_type operator)
{
	if (operator == TOKEN_AND)
		return (create_logical_node(NODE_AND, left, right));
	else if (operator == TOKEN_OR)
		return (create_logical_node(NODE_OR, left, right));
	return (NULL);
}

t_ast *parse_logical_rec(t_token **tokens, const char *input, t_ast *left)
{
	t_token *current;
	t_ast *right;
	t_token_type operator;

	while (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
	{
		operator = (*tokens)->type;
		current = *tokens;
		*tokens = (*tokens)->next;
		free_token(current);
		right = parse_pipeline(tokens, input);
		if (!right)
		{
			free_ast(left);
			print_error(E_SYNTAX, "Invalid syntax after logical operator", 10);
			return (NULL);
		}
		left = update_logical_node(left, right, operator);
		if (!left)
		{
			free_ast(right);
			return (NULL);
		}
	}
	return (left);
}

t_ast *parse_logical_expression(t_token **tokens, const char *input)
{
	t_ast *left;

	left = parse_pipeline(tokens, input);
	if (!left)
		return (NULL);
	return (parse_logical_rec(tokens, input, left));
}
/* ************ */

t_ast *parse_tokens(t_token **tokens, const char *input)
{
	t_ast *ast;

	if (!tokens || !*tokens)
		return (NULL);

	ast = parse_logical_expression(tokens, input);
	if (!ast || *tokens)
	{
		free_ast(ast);
		free_token_list(*tokens);
		print_error(E_SYNTAX, "Invalid syntax", 10);
		return (NULL);
	}
	printf("LOG: parse_tokens completed. tokens at %p\n", (void *)*tokens);

	return (ast);
}

// -------PRINT-------------

void print_indentation(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		 printf("  ");
		 i++;
	}
}

// for test: print ast
void    print_ast(t_ast *ast, int depth)
{
	size_t	j;
	t_redir	*redir;

	if (!ast)
		return ;

	// indentation
	print_indentation(depth);
	
	//print type of node
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
		
	// print arg for NODE_CMD
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

		// print redir
		redir = ast->command->redirs;
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
				
			redir = redir->next;
		}
	}
	else
		printf("\n");
	
	// print recursive node
	print_ast(ast->left, depth + 1);
	print_ast(ast->right, depth + 1);
}



// for compilation without makefile

// gcc -Wall -Wextra etape1.c ./libft.a -lreadline
// gcc -g -Wall -Wextra etape1.c ./libft.a -lreadline
// valgrind --leak-check=full ./a.out


// step_1 : normalisation

char *prompt_input(char *prompt)
{
	char	*input = NULL;

	if (!prompt)
		return (NULL);
	input = readline(prompt);
	if (!input)
	{
		write(1, "exit\n", 5); // Gestion de Ctrl+D
		return (NULL);
	}
	if (*input) // add to history
		add_history(input);
	return (input);
}

// loop shell
int run_shell(void)
{
	char    *input = NULL;
	char    *prompt = NULL;
	t_token *tokens = NULL;
	t_ast   *ast = NULL;

	while (1)
	{
		prompt = format_prompt();
		if (!prompt || !*prompt)
		{
			ft_putstr_fd("Error: Unable to format prompt.\n", 2);
			return (1);
		}
		input = prompt_input(prompt); // print prompt
		free(prompt);

		if (!input)
		{
			printf("CTRL+D\n");
			break;
		}

		printf("=>\n\n enter in main\n");

		if (*input)
		{
			// step 2: Lexer : analyse lexicale without interpretation input
		printf("=> Analyser lexical: input to tokens\n");
		
			tokens = lexer(input);
			printf("out_lexer\n");
			if (!tokens)
			{
				printf("not token\n");
				status_manager(258, STATUS_WRITE);
				free(input);
				continue;
			}
			printf("\n");
			print_tokens(tokens);
			

			//print multiligne heredocs
			process_heredoc(tokens, input);
			
		   printf("\n\nLOG: Before parse_tokens, tokens at %p\n", (void *)tokens);
			
			// step 3 : parsing : interprete token to token
			ast = parse_tokens(&tokens, input);

			printf("LOG: After parse_tokens, tokens at %p\n", (void *)tokens);

			
			if (!ast)
			{
				printf("LOG: parse_tokens failed. Tokens at %p\n", (void *)tokens);
				status_manager(258, STATUS_WRITE);
				// free_token_list(tokens);
				// free(input);
				continue;
			}
			
			printf("\n\nAbstract Syntax Tree (AST):\n");
			print_ast(ast, 0);
			
			free_ast(ast);
			ast = NULL;
			
			free_token_list(tokens);
			tokens = NULL;
			// free(input);
		}
		free(input);
		printf("End_loop\n");
	}
	// rl_clear_history();
	return (0);
	
}



int main(int argc, char **argv)
{
	check_args(argc, argv);       // Vérificator args
	setup_signals();             // Config signals
	run_shell(); 				// Manage mibishell
	
	return (EXIT_SUCCESS);
} 
