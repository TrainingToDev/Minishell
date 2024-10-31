/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:12:13 by miaandri          #+#    #+#             */
/*   Updated: 2024/10/31 16:25:51 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char    *get_command(char *input)
{
    int i;
    char *command;
    
    command = (char*)malloc(sizeof(char) * ft_strlen(input) + 1);
    if (!command)
        return (NULL);
    i = 0;
    while (input[i])
    {
        command[i] = input[i];
        i++;
    }
    command[i] = '\0';
    return (command);
}

static char    *get_option(char *input)
{
    int i;
    char *option;
    
    if (ft_strlen(input) != 2)
        return (NULL);
    i = 0;
    while(input[i])
    {
        if (input[0] != '-')
            return (NULL);
        else
        {
            if (isalpha(input[1]) == 0)
            {
                option = (char*)malloc(sizeof(char) * 3);
                if (!option)
                    return (NULL);
                option[0] = input[0];
                option[1] = input[1];
                option[2] = '\0';
                return (option);
            }
            return (NULL);
        }
    }
}

static char *get_param(char *input)
{
    
}
static int  get_len(char **split)
{
    int i;

    i = 0;
    while (split[i])
        i++;
    return (i);
}

t_parse  *get_struct(char *input)
{
    char **splited;
    t_parse *data;
    int len;

    data = (t_parse *)malloc(sizeof(t_parse));
    if (!data)
        return (NULL);
    splited = ft_split(input, ' ');
    len = get_len(splited);
    data->command = get_command(*splited);
    data->option = get_option(splited[2]);
    if (data->option == NULL)
    {
        
    }
    
}
