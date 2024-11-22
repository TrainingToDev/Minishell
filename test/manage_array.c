/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 11:41:56 by miaandri          #+#    #+#             */
/*   Updated: 2024-11-20 11:41:56 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *get_state(char *input)
{
    char **token;
    int i;
    t_token *tok;

    token = tokening(input);
    tok = NULL;
    i = 0;
    if(!token || !input)
        return(NULL);
    while (token[i])
    {
        add_new_token(&tok, g_token(token[i]));
        i++;
    }
    while (i >= 0)
    {
        free(token[i]);
        i--;
    }
    free(token);
    free (input);
    return (tok);
}
t_token **get_all_token(char **data, int len)
{
    t_token **array;
    int i;

    i = 0;
    if (!data)
        return (NULL);
    array = (t_token**)malloc(sizeof(t_token*) * (len + 1));
    if (!array)
        return (NULL);
    while (i < len)
    {
        array[i] = get_state(ft_strdup(data[i]));
        i++;
    }
    array[i] = NULL;
    while (i > 0)
    {
        if (data[i])
            free(data[i]);
        i--;
    }
    free(data);
    return (array);
}
/*
void    attribute_state(t_token *tok)
{

}
*/

void    get_all_state(t_token **all)
{
    int i;

    i = 0;
    while (all[i])
    {
        while (all[i]->next)
        {
            is_redir(&all[i]);
            is_heredoc(&all[i]);
            is_input_file(&all[i]);
            command(&all[i]);
            printf("the new state is : %i for the token : %s\n", all[i]->state, all[i]->token);
            if (all[i]->next != NULL)
                all[i] = all[i]->next;
        }
        if (all[i] != NULL)
        {
            is_redir(&all[i]);
            is_heredoc(&all[i]);
            is_input_file(&all[i]);
            command(&all[i]);
            printf("the new state is : %i for the token : %s\n", all[i]->state, all[i]->token);
        }
        i++;
    }
}
