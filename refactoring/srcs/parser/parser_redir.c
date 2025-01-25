#include "minishell.h"

t_redir_type convert_token_to_redir_type(t_token_type token_type)
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

static int validate_redir_token(t_parser *parser, t_redir *redir)
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

static int handle_heredoc(t_parser *parser, t_redir *redir, char *input)
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

static int process_redirection(t_parser *parser, t_redir *redir, char *input)
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

t_redir *parse_io_redirect(t_parser *parser, char *input)
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