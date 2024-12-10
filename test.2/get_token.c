/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 07:38:55 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/18 14:11:05 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int number_token(char *input)
{
    int i;
    int num;

    i = 0;
    num = 0;
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            i = quote_case(input, i);
            if (input[i + 1] == ' ' || input[i + 1] == '\0')
                num++;
        }
        else  if (input[i] != ' ' && input[i + 1] == ' ')
            num++;
        else if (input[i] != ' ' && input[i + 1] == '\0')
            num++;
        i++;
    }
    return (num);
}

static int get_len(char *input, int start)
{
    int i;

    i = start;
    while (input[i])
    {
        i = quote_case(input, i);
        if (input[i] == ' ' || input[i] == '\0')
            return (i - start);
        i++;
    }
    return (i - start);
}

static char **split_token(char *input, char **token)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    while (j < number_token(input) && input[i])
    {
        if (input[i] == ' ')
            i++;
        else
        {
            len = get_len(input, i);
            token[j] = ft_substr(input, i, len);
           // printf("token: %i->%s\n",  j, token[j]);
            j++;
            i += len + 1;
        }
    }
    token[j] = NULL;//don't understand
    return (token);
}

char **tokening(char *input)//split par espace a chaque de chaque pile d'exec
{
    char **token;

    if (!input)
        return (NULL);
    //printf("number token: %i\n", number_token(input));
    token = (char**)malloc(sizeof(char*) * (number_token(input) + 1));
    if (!token)
        return (NULL);
    token = split_token(input, token);
    return (token); 
}
