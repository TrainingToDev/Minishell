/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:12:13 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 09:46:21 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char    *get_command(char *input, int len)
{
    int i;
    char *command;
    
    command = (char*)malloc(sizeof(char) * len);
    if (!command)
        return (NULL);
    i = 0;
    while (i < len)
    {
        command[i] = input[i];
        i++;
    }
    command[i] = '\0';
    return (command);
}

static char    *get_option(char *input, int i)
{
    char *option;
    
    if (input[i] != '-')
        return (NULL);
    i++;
    if (is_alpha(input[i]) == 1)
    {
        option = (char *)malloc(sizeof(char) * 3);
        if (!option)
            return (NULL);
        option[0] = '-';
        option[1] = input[i];
        option[2] = '\0';
        return (option);
    }
    return (NULL);
}

static char *get_param(char *input, int len, int i)
{
    char *param;
    int c;

    c = 0;
    param = (char*)malloc(sizeof(char) * len);
    if (!param)
        return (NULL);
    while (input[i])
    {
        param[c] = input[i];
        i++;
        c++;
    }
    param[c] = '\0';
    return (param);
}

t_parse  *get_struct(char *input)
{
    t_parse *data;
    int i;
    int len;

    data = (t_parse *)malloc(sizeof(t_parse));
    if (!data)
        return (NULL);
    data->command = NULL;
    data->option = NULL;
    data->param = NULL;
    i = 0;
    while (input[i] && input[i] != ' ')
        i++;
    data->command = get_command(input, (i));
    if (input[i] == '\0')
    {
        free (input); 
        return (data);
    }
    while (input[i] == ' ' && input[i])
        i++;
    data->option = get_option(input, i);
    if (data->option != NULL)
        i = i + 2;
    if (input[i] == '\0')
    {
        free (input);
        return (data);
    }
    len = 0;
    while (input[i] == ' ')
        i++;
    while (input[i])
    {
        len++;
        i++;
    }
    data->param = get_param(input, (len + 1), (i - len)); 
    free (input);
    return (data);
}

