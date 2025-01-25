#include "minishell.h"

int consecutive_redir_in(const char *input)
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

int	unsupported_redirs(const char *input)
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
