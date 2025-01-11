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

static int existing(char *var, t_export *exp)
{
    t_export *temp;
    int i;

    i = 0;
    temp = exp;
    while(temp)
    {
        if (ft_strncmp(var, temp->var, ft_strlen(var)) == 0)
        {
            free(var);
            return (i);
        }
        i++;
        temp = temp->next;
    }
    free (var);
    return (-1);//don't exist state
}

static char *get_var(char *tok, int c)
{
    int i;
    char *var;

    var = NULL;
    i = 0;
    while(tok[i])
    {
        if (tok[i] == c)
        {
            var = get_string(tok, 0, i, '=');
            return (var);   
        }
        i++;
    }
    return (var);
}

static void ft_free(char **splitted, int len)
{
    while(len >= 0)
    {
        free(splitted[len]);
        len--;
    }
    free (splitted);
}


static char *reform_value(char *value)
{
    char *tmp;
    char *reformed;

    if (value[0] == '"')
    {
        reformed = ft_strjoin("=", value);
    }
    else
    {
        tmp = ft_strjoin("=\"", value);
        reformed = ft_strjoin(tmp, "\"");
        free (tmp);
    }
    free (value);
    return (reformed);
}
static char *get_value(char *tok)
{
    char **splitted;
    char *value;
    int a;
    int i;

    i = 0;
    a = 1;
    value = "";
    splitted = ft_split(tok, '=');
    while(splitted[i])
        i++;
    if (i != 1)
    {
        while(splitted[a])
        {
            value = ft_strjoin(value, splitted[a]);
            a++;
        }
    }
    else
        value = ft_strdup(splitted[1]);
    ft_free (splitted, i);
    value = reform_value(value);
    return (value);
}

static void remplace(t_export **exp, char *token, int i)
{
    t_export *temp;

    temp = (*exp);
    while(i > 0)
    {
        i--;
        temp = temp->next;
    }
    free(temp->value);
    temp->value = get_value(token);
}

int export_command(t_env *env, t_token **token, t_export *exp)
{
    t_export *temp2;
    int state;

    temp2 = exp;
    state = 0;
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
            state = existing(get_var((*token)->token, '='), exp); 
            if (state >= 0)
            {
                printf("exp state : %i\n", state);
                remplace(&exp, (*token)->token, state);
            }
            else
            {
                add_new_exp(&exp, new_export(reform((*token)->token)));
                if(is_env((*token)->token) == 1)
                    add_new_env(&env, new_env((*token)->token));
                if(is_env((*token)->token) == 2)
                    add_new_env(&env, new_env(reform((*token)->token)));
            }
        }
        (*token) = (*token)->next;
    }
    return (0);
}
