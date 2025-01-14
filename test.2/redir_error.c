/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 07:25:57 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-10 07:25:57 by miaandri         ###   ########.fr       */
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

static int test2_2(char *input, int i)
{
    int count;

    count = 0;
    while (input[i])
    {
        i = quote_case(input, i);
        while(input[i] == '>' && input[i])
        {
            i++;
            count++;
        }
        if (count > 2)
            return (write (2, "syntax error near unexpected token `>>'\n", 40));
        count = 0;
        if (input[i] != '\0')
            i++;
    }
    return (0);
}

int test2(char *input, int i)//redir +2 mifanesy
{
    int count;

    count = 0;
    if (test2_2(input, i) != 0)
        return (-1);
    while (input[i])
    {
        while (input[i] == '<' && input[i])
        {
            i++;
            count++;
        }
        if (count > 2)
            return (write (2, "syntax error near unexpected token `<<'\n", 40));
        count = 0;
        if (input[i] != '\0')
            i++;
    }
    return (0);
}

static int test3_2(char *input, int i)//test <>> || <><
{
    if (input[i] == '<')
    {
        if (input[i + 1] && input[i + 1] == '>')
        {
            if (input[i + 2] && (input[i + 2] == '>' || input[i + 2] == '<'))
            {
                error(1);
                return (-1);
            }
        }
    }
    if (input[i] == '<')
    {
        if (input[i + 1] && input[i + 1] == '>')
           return (write (2, "Our shell don't handle that\n", 28)); 
    }
    return (0);
}

int test3(char *input, int i)//test >< || ><< 
{
    if (test3_2(input, i) != 0)
        return (-1);
    if (input[i] == '>')
    {
        if (input[i + 1] == '<')
        {
            error(1);
            return (-1);
        }
    }
    if (input[i] == '>')
    {
        if (input [i + 1] && input[i + 1] == '<')
        {
            if (input[i + 2] && (input[i + 2] == '<' || input[i + 2] == '>'))
            {
                error(1);
                return (-1);
            }
        }
    }
    return (0);
}

static int test4_2(char *input, int i)
{
    if (input[i] == '<')
    {
        if (input[i + 1] == '\0')
        {
            printf("here ");
            return (-1);
        }
        i++;
        if (input[i] && input[i] == '<')
            i++;
        while (input[i])
        {
            if (is_space(input[i]) != 1)
                return (0);
            i++;
        }
        error(0);
        return (-1);
    }
    return (1);
}

int test4(char *input , int i)//test after redir there nothing else than space 
{
    if (test4_2(input, i) == -1)
        return (-1);
    if (input[i] == '>')
    {
        if (input[i + 1] == '\0')
        {
            error(0);
            return (-1);
        }
        i++;
        if (input[i] && (input[i] == '>'))
            i++;
        while (input[i])
        {
            if (is_space(input[i]) == 0)
                return (0);
            i++;
        }
        error(0);
        return (-1);
    }
    return (0);

}

int test1(char *input, int i)//test for pipe and redirection successive or separated by space
{
    i++;
    if (input[i] == '|')
        return (write (2, "Our shell don't handle that\n", 28));
    if (input[i] == '>' || input[i] == '<')
        i++;
    while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|')
    {
        if (is_space(input[i]) == 0)
            return (0);
        i++;
    }
    if (input[i] == '\0')
        return (0);
    if (input[i] == '<' || input[i] == '>')
        return ( write (2, "syntax error near unexpected token `< or >'\n", 46));
    if (input[i] == '|')
        return (write (2, "Our shell don't handle that\n", 28));
    return (0);
}
