#include "minishell.h"

t_token_type get_op_token(const char *str)
{
	if (ft_strncmp(str, ">|", 2) == 0)
		return (TOKEN_REDIRECT_OUT);
	if (ft_strncmp(str, "&&", 2) == 0)
		return (TOKEN_AND);
	else if (ft_strncmp(str, "||", 2) == 0)
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
	else if (*str == '(')
		return (TOKEN_LPAREN);
	else if (*str == ')')
		return (TOKEN_RPAREN);
	else
		return (TOKEN_UNKNOWN);
}

int is_operator(const char *str)
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

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
