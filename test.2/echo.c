/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:21:52 by miaandri          #+#    #+#             */
/*   Updated: 2024/12/22 21:18:54 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
  //  if (exact_command(data->option, "-n") != 1)  
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


*/

static int check_option(t_token *token)//state 1 : option exist
{
    t_token *temp;

    temp = token;
    while(temp)
    {
        if (ft_strncmp(temp->token, "-n", ft_strlen("-n")) == 0)
            return (1);
        temp = temp->next;
    }
    return (0);
}

static char check_redir(t_token *token)
{
    char *redir;
    t_token *temp;

    redir = NULL
    temp = token;
    while(temp)
    {
        if (temp->state == 5)
            redir = temp->token;
        temp = temp->next;
    }
    return(redir);
}

int echo_command(t_token **token)
{
    while((*token))
    {
        if ((*token)->state == 6)
            printf("%s", (*token)->token);
        (*token) = (*token)->next; 
    }
    if (check_option(*token) == 0)
        printf("\n");
    return(0);//valeur de retour ny $?
}