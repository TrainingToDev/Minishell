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

static int check(char *token)
{
    int i;

    i = 0;
    while (token[i])
    {
        i = quote_case(token, i);
        if (token[i] == '>' || token[i] == '<')
            return (1);
        i++;
    }
    return (0);
}

void command (t_token **tok)
{
    int i;

    i = 0;
    if ((*tok)->state != 0)
        return ;
    while ((*tok)->token[i])
    {
        if (is_alpha((*tok)->token[i]) == 0)
            return ;
        i++;
    }
        (*tok)->state = 1;
}

void  is_redir(t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    if (ft_strnstr((*tok)->token, ">>", ft_strlen((*tok)->token)) != NULL && ft_strlen((*tok)->token) == 2)
    {
        if ((*tok)->next != NULL)
        {
            (*tok) = (*tok)->next;
            if (check((*tok)->token) == 0)
                (*tok)->state = 2;
            else if (check((*tok)->token) == 1)
                (*tok)->state = 20; 
        }
        else
            (*tok)->state = -1;
    }
    else if (ft_strnstr((*tok)->token, ">>", ft_strlen((*tok)->token)) != NULL)
    {
        if (check((*tok)->token) == 0)
            (*tok)->state = -2;
        else if (check((*tok)->token) == 1)
            (*tok)->state = -20;
    }
}

void    is_heredoc(t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    if (ft_strnstr((*tok)->token, "<<", ft_strlen((*tok)->token)) != NULL && ft_strlen((*tok)->token) == 2)
    {
        if ((*tok)->next != NULL)
        {
            (*tok) = (*tok)->next;
        if (check((*tok)->token) == 0)
            (*tok)->state = 3;
        else if (check((*tok)->token) == 1)
            (*tok)->state = 30; 
        }
        else
            (*tok)->state = -1;
    }
    else if (ft_strnstr((*tok)->token, "<<", ft_strlen((*tok)->token)) != NULL)
    {
        if (check((*tok)->token) == 0)
            (*tok)->state = -3;
        else if (check((*tok)->token) == 1)
            (*tok)->state = -30;
    }
}

void    is_input_file(t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    if (ft_strnstr((*tok)->token, ">", ft_strlen((*tok)->token)) != NULL && ft_strlen((*tok)->token) == 1)
    {
        if ((*tok)->next != NULL)
        {
            (*tok) = (*tok)->next;
            if (check((*tok)->token) == 0)
                (*tok)->state = 4;
            else if (check((*tok)->token) == 1)
                (*tok)->state = 40; 
        }
        else
            (*tok)->state = -1;
    }
    else if (ft_strnstr((*tok)->token, ">", ft_strlen((*tok)->token)) != NULL)
    {
        if (check((*tok)->token) == 0)
            (*tok)->state = -4;
        else if (check((*tok)->token) == 1)
            (*tok)->state = -40;
    }
}

void    is_output_file(t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    if (ft_strnstr((*tok)->token, "<", ft_strlen((*tok)->token)) != NULL && ft_strlen((*tok)->token) == 1)
    {
        if ((*tok)->next != NULL)
        {
            (*tok) = (*tok)->next;
            if (check((*tok)->token) == 0)
                (*tok)->state = 5;
            else if (check((*tok)->token) == 1)
                (*tok)->state = 50; 
        }
        else
            (*tok)->state = -1;
    }
    else if (ft_strnstr((*tok)->token, "<", ft_strlen((*tok)->token)) != NULL)
    {
        if (check((*tok)->token) == 0)
            (*tok)->state = -5;
        else if (check((*tok)->token) == 1)
            (*tok)->state = -50;
    }
}