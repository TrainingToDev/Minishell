/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:14:35 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/15 08:39:32 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_len(char *input, int start)
{
    int i;

    i = start;
    while (input[i])
    {
        i = quote_case(input, i);
        if (input[i] == '|' || input[i] == '\0')
            return (i);
        i++;
    }
    return (i);
} 


static char **get(char **data, char *input)
{
    int j;
    int i;
    int len;
    
    j = 0;
    i = 0;
    while (j < valid_pipe(input) && input[i])
    {
        len = get_len(input, i) - i;
        data[j] = ft_substr(input, i, len);
        printf("exec : %s\n", data[j]);
        j++;
        i += (len + 1);
    }
    data[j] = NULL;
    return (data);
}


char **get_pile(char *input)//splited by "|"                                                            
{
    char **data;
    
    if (!input)
        return (NULL);
    data = (char**)malloc(sizeof(char*) * (valid_pipe(input) + 1));
    if (!data)
        return (NULL);
    data = get(data, input);
    free(input);
    return (data);
}
