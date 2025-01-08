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

static char *copy_with_quote(char *old, char *new)
{
    int i;
    int j;
    int check;
    
    i = 0;
    j = 0;
    check = 0;
    while (old[i])
    {
        if (old[i] == '=' && old[i + 1] != '"')
        {
            new[j++] = old[i++];
            new[j++] = '"';
            check = 1;
        }
        else
            new[j++] = old[i++];
    }
    if (check == 1)
        new[j++] = '"';
    new[j] = '\0';
    return (new);
}

char *reform(char *old)//get_on the quote
{
    int i;
    int j;
    int check;
    char *dest;

    i = 0;
    j = 0;
    check = 0;
    dest = NULL;
    dest = (char*)malloc(sizeof(char) * ft_strlen(old) + 3);
    if (!dest)
        return (NULL);
    dest = copy_with_quote(old, dest);
    printf("dest : %s -> %i -> %i\n", dest, (int)ft_strlen(dest), (int)ft_strlen(old));
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
            write (2,"No argument is tolerated\n", 27);
            return (2);////$? = 2 when the option don ' t exist
        }
        else if ((*token)->state == 6)
        {
            add_new_exp(&exp, new_export(reform((*token)->token)));
            if(is_env((*token)->token) == 1)
                add_new_env(&env, new_env((*token)->token));
            if(is_env((*token)->token) == 2)
                add_new_env(&env, new_env(reform((*token)->token)));
        }
        (*token) = (*token)->next;
    }
    return (0);
}
