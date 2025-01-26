#include "minishell.h"

static size_t skip_and_get_var_length(const char *src, size_t *i)
{
    size_t  start;

	(*i)++;
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

char *append_var_value(const char *src, size_t *i, char *result, t_minishell *shell)
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
