/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 07:01:49 by miaandri          #+#    #+#             */
/*   Updated: 2025-01-13 07:01:49 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char *get_var(char *tok)
{
    char *var;
    char **va;

    var = NULL;
    va = ft_split(tok, '=');
    var = ft_strdup(va[0]);
    ft_free(va);
    return (var);
}

static char *reform_value(char *value)
{
    char *tmp;
    char *reformed;

    if (value[0] == '"')
        return (value);
    else
    {
        tmp = ft_strjoin("\"", value);
        reformed = ft_strjoin(tmp, "\"");
        free (tmp);
    }
    free (value);
    return (reformed);
}
char *get_value(char *tok)
{
    char **splitted;
    char *value;
    int a;
    int i;

    i = 0;
    a = 1;
    value = "";
    splitted = ft_split(tok, '=');
    if (ft_strncmp(tok, splitted[0], ft_strlen(tok)) == 0)
        return (ft_strdup(""));
    while(splitted[i])
        i++;
    if (i != 2)
    {
        while(splitted[a])
        {
            value = ft_strjoin(value, splitted[a]);
            if (a < i)
                value = ft_strjoin("=", splitted[a]);
            a++;
        }
        value = reform_value(value);
    }
    else
        value = ft_strjoin("=", reform_value(ft_strdup(splitted[1])));
    ft_free (splitted);
    return (value);
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
        if (old[i] == '=' && old[i + 1] != '"' && j + 1 < size)
        {
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