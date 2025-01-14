/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 07:52:24 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-10 07:52:24 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int specific_pipe(char *input, int i)
{
    int temp;

    temp = 0;
    while (i >= 0)
    {
        while (i >= 0 && is_space(input[i]) == 1)
        {
            i--;
            temp = i;
        }
        if (temp == i && input[i] == '<')
            return (write (2, "syntax error near unexpected token `|'\n",40));
        if (temp == i && input[i] == '>')
            return (write (2, "syntax error near unexpected token `|'\n",40));
        i--;
    }
    return (0);
}

static int void_pipe_left(char  *input, int i)
{
    while (i > 0)
    {
        i--;
        if (is_space(input[i]) != 1)
            return (1);
    }
    write (2, "syntax error near unexpected token `|'\n",40);
    return (-1);
}
static int void_pipe_right(char *input, int i)
{
    i++;
    while (input[i] != '|' && input[i])
    {
        if (is_space(input[i]) != 1)
            return (1);
        i++;
    }
    write (2, "syntax error near unexpected token `|'\n",40);
    return (-1);
}
int pipe_void(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        i = quote_case(input, i);
        if (input[i] == '|')
        {
            if (specific_pipe(input, i) != 0)
                return (-1);
            if (void_pipe_right(input, i) == -1)
                return (-1);
            if (void_pipe_left(input, i) == -1)
                return (-1);
        }
        i++;
    }
    return (0);
}

int check_redir(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '"' || input[i] == '\'')
            i = quote_case(input, i);
        else if (input[i] == '>' || input[i] == '<')
        {
            if (test4(input, i) != 0)
            {
                //printf ("test 4\n");
                return (-1);
            }
            if (test2(input, i) != 0)
            {
                //printf ("i'm in test2\n");
                return (-1);
            }
            if (test3(input, i) != 0)
            {
                //printf ("i'm in test3\n");
                return (-1);
            }
            if (test1(input, i) != 0)
            {
                //printf ("i'm in test1\n");
                return (-1);
            }
        }
        i++;
    }
    return (0);
}



