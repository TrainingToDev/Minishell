/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:01:43 by miaandri          #+#    #+#             */
/*   Updated: 2024/12/10 22:31:06 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *compare(char *var, t_env *env)
{
    t_env *temp;

    temp = env;
    while (temp)
    {
        if (ft_strncmp(var, temp->var, ft_strlen(var)) == 0)
        {
            free(var);
            var = ft_strdup(temp->value);
            return (var);
        }
        temp = temp->next;
    }
    return (var);
}

char *expand(char *input, int i, t_env *env)
{
    char *str1;
    char *str2;
    char *var;
    int c;

    str1 = ft_substr(input, 0, i);
    c = i;
    while(input[i] && input[i] != ' ')
        i++;
    var = ft_substr(input, c, i - c);
    if (input[i] == '\0')
        str2 = NULL;
    else
    {
        c = i;
        while(input[i])
            i++;
        str2 = ft_substr(input, c, i - c);
    }
    free(input);
    input = ft_strjoin_free(str1, var);
    input = ft_strjoin_free(input, str2);
    return (input);
}

char *new_expand(char *input)
{
    int i;
    int count;

    i = 0;
    while(input[i])
    {
        count = 0;
        while(input[i] && input[i] == '$')
        {
            count++;
            i++;
        }
        if (count != 0 && (count % 2) != 0)
            input = expand(input, i);
        i++;
    }
    return (input);
}
