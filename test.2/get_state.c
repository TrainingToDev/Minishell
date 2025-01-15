/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 11:45:02 by miaandri          #+#    #+#             */
/*   Updated: 2024-11-20 11:45:02 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int check2(char *token)
{
    int i;
    int check;

    i = 0;
    check = 0;
    while (token[i])
    {
        i = quote_case(token, i);
        if (token[i] == '>' || token[i] == '<')
        {
            if (token[i + 1] == '>' || token[i + 1] == '<')
                i++;
            check++;
        }
        i++;
    }
    if (check != 1)
        return (1);
    else 
        return (0);
}

void command (t_token **tok)
{
    if ((*tok)->state != 0 || (*tok)->check != 0)
        return ;
    (*tok)->state = 1;
    (*tok)->check = 1;
    if (count_quote((*tok)->token) != 0)
    {
        (*tok)->token = get_off_quote((*tok)->token, count_quote((*tok)->token));
        printf ("new command : %s\n", (*tok)->token);
    }
}

void  is_redir(t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    if (ft_strnstr((*tok)->token, ">>", ft_strlen((*tok)->token)) != NULL)
    {
        if (check2((*tok)->token) == 0)
        {
            (*tok)->token = reform_double((*tok)->token);
            (*tok)->state = 2;
        }
    }
}

void    is_heredoc(t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    if (ft_strnstr((*tok)->token, "<<", ft_strlen((*tok)->token)) != NULL)
    {
        if (check2((*tok)->token) == 0)
        {
            (*tok)->state = 3;
            (*tok)->token = reform_double((*tok)->token);
        }
    }
}

void    is_input_file(t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    if (ft_strnstr((*tok)->token, "<", ft_strlen((*tok)->token)) != NULL)
    {
        if (check2((*tok)->token) == 0)
        {
            (*tok)->token = reform_simple((*tok)->token);
            (*tok)->state = 4;
        }
    }
}

void    is_output_file(t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    if (ft_strnstr((*tok)->token, ">", ft_strlen((*tok)->token)) != NULL)
    {
        if (check2((*tok)->token) == 0)
        {
            (*tok)->token = reform_simple((*tok)->token);
            (*tok)->state = 5;
        }
    }
}

void    is_argument(t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    else
    {
        (*tok)->state = 6;
    }
}
