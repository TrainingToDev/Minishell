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

void command (t_token **tok)
{
    if ((*tok)->state != 0)
        return ;
    if (ft_strnstr((*tok)->token, ">", ft_strlen((*tok)->token)) == NULL && 
            ft_strnstr((*tok)->token, ">", ft_strlen((*tok)->token)) == NULL)
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
            (*tok)->state = 2; 
        }
        else
            (*tok)->state = -1;
    }
    else if (ft_strnstr((*tok)->token, ">>", ft_strlen((*tok)->token)) != NULL)
        (*tok)->state = -2;
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
            (*tok)->state = 3;
        }
        else
            (*tok)->state = -1;
    }
    else if (ft_strnstr((*tok)->token, "<<", ft_strlen((*tok)->token)) != NULL)
        (*tok)->state = -3;
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
            (*tok)->state = 4;
        }
        else
            (*tok)->state = -1;
    }
    else if (ft_strnstr((*tok)->token, ">", ft_strlen((*tok)->token)) != NULL)
        (*tok)->state = -4;
}