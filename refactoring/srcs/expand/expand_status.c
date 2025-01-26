#include "minishell.h"

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

char *process_dollar(const char *src, size_t *i, char *result, t_minishell *shell)
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
