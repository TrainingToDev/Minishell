/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-21 09:08:19 by miaandri          #+#    #+#             */
/*   Updated: 2024-11-21 09:08:19 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void error(int i)
{
    if (i == 0)
        write (2, "syntax error near unexpected token `newline'\n", 45);
    else if (i == 1)
        write (2, "syntax error near unexpected token `<'\n", 39);
}

int test2(char *input, int i)//redir +2 mifanesy
{
    char c1;
    char c2;

    c1 = '>';
    c2 = '<';
    while (input[i])
    {
        i = quote_case(input, i);
        if (input[i] == c1 || input[i] == c2)
        {
            if ((input[i + 1] == c1 || input[i + 1] == c2) && (input[i + 2] == c1|| input[i + 2] == c2))
            {
                error (1);
                return (-1);
            }
        }
        i++;
    }
    return (0);
}

int test1(char *input, int i)
{
    while (input[i])
    {
        if (input[i] != ' ')
            return (0);
        i++;
    }
    error(0);
    return (-1);
}

int test3(char *input, int i)
{
    if (input[i] == '>')
    {
        if (input[i + 1] == '<')
        {
            error(1);
            return (-1);
        }
    }
    return (0);
}

int test4(char *input, int i)
{
    int check;

    check = 0;
    if (input[i] == '>' || input[i] == '<')
    {
        i++;
        while (input[i] && (input[i] != '>' || input[i] != '<'))
        {
            if (input[i] != ' ')
            {
                printf ("%c : here\n", input[i]);
                 return (0);
            }
            i++;
        }
        if (input[i] == '\0')
        {
            error(0);
            return (-1);
        }
        else if (input[i] == '>' || input[i] == '<')
        {
            error(1);
            return (-1);
        }
    }
    return (0);
}
