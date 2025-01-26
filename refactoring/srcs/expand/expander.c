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

static char *append_char_to_result(char *result, char c)
{
    char	*temp;

	temp = ft_strjoin_char(result, c);
	free(result);
	return (temp);
}


static char	*process_normal_char(const char *src, size_t *i, char *result)
{
	result = append_char_to_result(result, src[*i]);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}

static char *process_dollar(const char *src, size_t *i, char *result, t_minishell *shell)
{
    if (src[*i + 1] == '?')
    {
		result = append_exit_status(result, shell);
		if (!result)
			return (NULL);
		*i += 2;
	}
	else
	{
		result = append_var_value(src, i, result, shell);
		if (!result)
			return (NULL);
	}
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
