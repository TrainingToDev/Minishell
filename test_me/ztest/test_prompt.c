/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:55:48 by herandri          #+#    #+#             */
/*   Updated: 2024/11/17 13:37:17 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

# define COLOR_RESET "\033[0m"
# define COLOR_GREEN "\033[32m"

// version with test basic

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
	return (prompt);
}

int main(void)
{
    char *input;
 
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