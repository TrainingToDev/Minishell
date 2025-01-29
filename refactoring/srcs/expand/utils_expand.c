/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:03:35 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/29 06:45:56 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*compare(char *key, t_env_var *env)
{
	t_env_var	*temp;
	char		*value;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(key, temp->key, ft_strlen(temp->key)) == 0
			&& ft_strlen(key) == ft_strlen(temp->key))
		{
			value = ft_strdup(temp->value);
			return (value);
		}
		temp = temp->next;
	}
	return (ft_strdup(""));
}

char	*ft_strjoin_free(char *s1, char *s2, int free_flag)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	if (free_flag == 1 || free_flag == 3)
		free(s1);
	if (free_flag == 2 || free_flag == 3)
		free(s2);
	return (result);
}

char	*ft_strjoin_char(char *s, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(s);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

int	is_single_quoted(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	return (len >= 2 && str[0] == '\'' && str[len - 1] == '\'');
}
