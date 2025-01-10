/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-27 09:58:22 by miaandri          #+#    #+#             */
/*   Updated: 2024-12-27 09:58:22 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_option(char *arg)
{
    int i;
    
    i = 0;
    while (arg[i])
    {
        if (arg[i] == '-' && i == 0)
        {
            i++;
            if (is_alpha(arg[i]) == 1)
                return (1);
        }
        i++;
    }
    return (0);
}

static int is_env(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '=')
        {
            if (arg[i + 1])
                return (1);
            return (2);
        }
        i++;
    }
    return (0);
}
// add size
static char *copy_with_quote(char *old, char *new, int size)
{
    int i;
    int j;
    int check;
    
    i = 0;
    j = 0;
    check = 0;
    while (old[i])
    {
        if (j >= size - 1) // check overflow j
            break ;
        if (old[i] == '=' && old[i + 1] != '"')
        {
            if (j + 2 >= size - 1) // check '=' and '"'
                break ;
            new[j++] = old[i++];
            new[j++] = '"';
            check = 1;
        }
        else
            new[j++] = old[i++];
    }
    if (check == 1 && j < size - 1) // check overflow j
        new[j++] = '"';
    new[j] = '\0';
    return (new);
}

char *reform(char *old)//get_on the quote
{
    // int i = 0;
    // int j = 0;
    // int check = 0;
    char *dest;
    int size;

    size = ft_strlen(old) + 3;
    dest = NULL;
    dest = (char*)malloc(sizeof(char) * size);
    if (!dest)
        return (NULL);
    dest = copy_with_quote(old, dest, size); // add size to param
    // printf("dest : %s -> %i -> %i\n", dest, (int)ft_strlen(dest), (int)ft_strlen(old));
    return (dest);
}

static int export(t_export *exp)//export without option and argument
{
    while (exp)
    {
        printf("%s", exp->proto);
        printf("%s", exp->var);
        printf("%s\n", exp->value);
        exp = exp->next;
    }
    return (0);
}
/*
static int export_existing(t_export *env, t_export *new)
{
    t_export *temp;

    temp = env;
    while (temp)
    {
        if (ft_strncmp(temp->var, new->var, ft_strlen(new->var)) == 0)
        {
            free (temp->value);
            temp->value = new->value;
            free(new->proto);
            free(new->var);
            free(new->value);
            free(new->next);
            free(new);
            return (1);
        }
        temp = temp->next;
    }
    free(new->proto);
    free(new->var);
    free(new->value);
    free(new->next);
    free(new);
    return (0);
}

static int env_existing(t_env *env, t_env *new)
{
    t_env *temp;

    temp = env;
    while (temp)
    {
        if (ft_strncmp(temp->var, new->var, ft_strlen(new->var)) == 0)
        {
            free (temp->value);
            temp->value = new->value;
            free(new->var);
            free(new->value);
            free(new->next);
            free(new);
            return (1);
        }
        temp = temp->next;
    }
    free(new->var);
    free(new->value);
    free(new->next);
    free(new);
    return (0);
}
*/

int export_command(t_env *env, t_token **token, t_export *exp)
{
    t_export *temp2;

    temp2 = exp;
    if (checking_redir((*token)) == 1)
        printf("need redirection function\n");
    if ((*token)->next == NULL)
        return (export(temp2));
    while ((*token))
    {
        if ((*token)->state == 6 && is_option((*token)->token) == 1)
        {
            write (2,"No argument is tolerated\n", 25); // update
            return (2);////$? = 2 when the option don ' t exist
        }
        else if ((*token)->state == 6)
        {
//            if (export_existing(exp, new_export(reform((*token)->token))) == 0)
                add_new_exp(&exp, new_export(reform((*token)->token)));
            if(is_env((*token)->token) == 1)// && env_existing(env, new_env((*token)->token)) == 0)//can add to env
                add_new_env(&env, new_env((*token)->token));
            if(is_env((*token)->token) == 2)//&& env_existing(env, new_env((*token)->token)) == 0)//can add to env but the value is null
                add_new_env(&env, new_env(reform((*token)->token)));
        }
        (*token) = (*token)->next;
    }
    return (0);
}
