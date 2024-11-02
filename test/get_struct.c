/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:12:13 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/02 16:23:27 by miaandri         ###   ########.fr       */
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
   // printf ("command : %s\n", command);
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

/*
static char *get_param(char *input)
{
    int len;
    int i;
    char    *param;

    i = 0;
    len = ft_strlen(input);
    printf ("%i\n", len);
    param = (char*)malloc(sizeof(char) * len + 1);
    if (!param)
        return (NULL);
    while (input[i])
    {
        param[i] = input[i];
        i++;
    }
    param[i] = '\0';
    printf("param : %s\n", param);
    return (param);
}
static int  check_pipe(char *split)
{
    if (ft_strlen(split) == 1)
    {
        if (split[0] == '|')
            return (1);
    }
    return (0);
}
static char *get_params(char **splited, t_parse *data)
{
    int i;

    i = 1;
    if (data->option != NULL)
        i = 2;
    while (splited[i])
    {
        if (check_pipe(splited[i]) == 1)
            return (data->param);
        data->param = ft_strjoin(data->param, get_param(splited[i]));
        i++;
    }
    return (data->param);
}
*/

t_parse  *get_struct(char *input)
{
    t_parse *data;
    int i;

    data = (t_parse *)malloc(sizeof(t_parse));
    if (!data)
        return (NULL);
            i = 0;
    while (input[i] != ' ' || input[i] == '\t')
        i++;
    data->command = get_command(input, (i + 1));
    while (input[i] == ' ' || input[i] == '\t')
    {   
        i++;
    }
    printf("::%i\n", i);
    data->option = get_option(input, i);

    printf("command : %s -> option : %s\n", data->command , data->option);
    return (data);
}

