#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

# define COLOR_RESET "\033[0m"
# define COLOR_GREEN "\033[32m"

// version with test basic

int get_display_length(const char *str) 
{
    int len = 0;
    while (*str) {
        if (*str == '\033')
        {
            while (*str && *str != 'm')
                str++;
        } 
        else
        {
            len++;
        }
        str++;
    }
    return len;
}


char	*get_prompt()
{
	char	*cwd;
	char	*prompt;
	char	*tmp;

	cwd = getcwd(NULL, 0);
    // printf("%d\n", get_display_length(cwd));
	if (!cwd)
	{
		cwd = ft_strdup("minishell");
		if (!cwd)
			return (NULL);
	}
	prompt = ft_strjoin("\001"COLOR_GREEN"\002", cwd);
	free(cwd);
	if (!prompt)
		return (NULL);
	tmp = prompt;
	prompt = ft_strjoin(prompt, "\001"COLOR_RESET"\002" " $ ");
    
	if (!prompt)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
    // prompt = cwd;
	return (prompt);
}

int main(void)
{
    char *input;
    // char *prompt = get_prompt();
    // if (!prompt)
    //     return (-1);

    while(1)
    {
        input = readline(get_prompt());
        if(!input)
            return (-1);
        add_history(input);
    }
    //printf("%s", input);

    return(0);
}