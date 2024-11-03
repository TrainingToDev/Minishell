/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:21:52 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/03 11:58:54 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_struct(t_parse *data)
{
    free(data->command);
    free(data->option);
    free(data->param);
    free (data);
}

static void print_echo(char *string, int i)//mbola mila zaraina roa de + ilay variable ilay echo + message d'erreur @ ilay cas heredoc iny 
{
    while (string[i])
    {
        if (string[i] == ' ' && string[i + 1] != ' ')
            printf(" ");
        else if (string[i] == ' ' && string[i + 1] == ' ')
            ;
        else if (string[i] == '"')
        {
            i++;
            while(string[i] != '"')
            {
                printf("%c", string[i]);
                i++;
            }
        }
        else if (string[i] == '\'')
        {
            i++;
            while(string[i] != '\'')
            {
                printf("%c", string[i]);
                i++;
            }
        }
        else
             printf("%c", string[i]);
        i++;
    }
}

int    echo_command(t_parse *data)
{
    if (exact_command(data->command, "echo") != 1)
        return (0);
    if (exact_command(data->option, "-n") != 1)  
        return (0);
    if (data->param == NULL)
    {
        free_struct(data);
        return (1);
    }
    else
    {
        print_echo(data->param, 0);
        free_struct(data);
        return (1);   
    }
    return (0);
}

int echo_without_option(t_parse *data)
{
    if (exact_command(data->command, "echo") != 1)
        return (0);
    if (data->param == NULL)
    {
        printf("\n");
        free_struct(data);
        return (1);
    }
    else
    {
        print_echo(data->param, 0);
        printf("\n");
        free_struct(data);
        return (1);   
    }
    return (0);
}

