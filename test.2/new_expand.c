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

int case_quote(char *input, int i)
{
    if (input[i] == '\'')
    {
        i++;
        while(input[i] && input[i] != '\'')
            i++;
    }
    return (i);
}
//
char *compare(char *var, t_env *env)
{
    t_env *temp;

    temp = env;
    while (temp)
    {
        if (ft_strncmp(var, temp->var, ft_strlen(var)) == 0)
        {
            free(var);
            var = ft_substr(env->value, 1, ft_strlen(env->value) - 1);
            return (var);
        }
        temp = temp->next;
    }
    free (var);
    return ("");
}

static char *expand_utils(char *str1, char *str2, char *var)
{
    char *input;

    if (ft_strlen(var) == 0 && ft_strlen(str1) != 0)
    {
        input = ft_strjoin(str1, var);
        free(str1);
    }
    else if (ft_strlen(str1) == 0 && ft_strlen(var) != 0)
    {
        input = ft_strjoin(str1, var);
        free(var);
    }
    else if (ft_strlen(str1) == 0 && ft_strlen(var) == 0)
        input = ft_strjoin(str1, var);
    else
        input = ft_strjoin_free(str1, var);
    if (ft_strlen(str2) == 0)
        input = ft_strjoin_f(input, str2);
    else
        input = ft_strjoin_free(input, str2);
    return (input);
}


char  *expand(char *input, int i, t_env *env)
{
    char *str1;
    char *str2;
    char *var;
    int c;

    str1 = ft_substr(input, 0, i - 1) ;
    c = i;
    while(input[i] && input[i] != ' ' && input[i] != '"')
        i++;
    var = ft_substr(input, c, i - c);
    var = compare(var, env);
    printf("compare %s -> %i\n", var, (int)ft_strlen(var));
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
    input = expand_utils(str1, str2, var);
    return (input);
}

char *new_expand(char *input, t_env *env)//expand en boucle
{
    int i;
    int count;
    int temp;

    i = 0;
    while(input[i])
    {
        i = case_quote(input, i);
        count = 0;
        temp = i;
        while(input[i] && input[i] == '$')
        {
            count++;
            i++;
        }
        if (count != 0 && (count % 2) != 0)
        {
            input = expand(input, i, env);
            i = temp;
            while (input[i] && input[i] != ' ')
                i++;
        }
        if (input[i] != '\0')
            i++;
    }
    return (input);
}
