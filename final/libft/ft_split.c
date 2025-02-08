/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 04:14:22 by herandri          #+#    #+#             */
/*   Updated: 2024/03/25 07:08:12 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		if (*s != c)
		{
			counter++;
			while (*s && *s != c)
				s++;
		}
		else if (*s == c)
			s++;
	}
	return (counter);
}

static char	*ft_str_until_char(char *s, char c)
{
	char	*dst;
	char	*tmp;

	tmp = s;
	while (*tmp && *tmp != c)
		tmp++;
	dst = (char *)malloc(sizeof(char) * (tmp - s + 1));
	if (!dst)
		return (NULL);
	tmp = dst;
	while (*s && *s != c)
	{
		*tmp = *s;
		tmp++;
		s++;
	}
	*tmp = '\0';
	return (dst);
}

static void	free_array(char **dst)
{
	char	**ptr;

	ptr = dst;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(dst);
}

static char	**split_and_allocate(char *str, char c, char **dst)
{
	int		i;

	i = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			dst[i] = ft_str_until_char(str, c);
			if (!dst[i])
			{
				free_array(dst);
				return (NULL);
			}
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	dst[i] = NULL;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**dst;

	if (!s)
		return (NULL);
	str = (char *)s;
	dst = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!dst)
		return (NULL);
	dst = split_and_allocate(str, c, dst);
	return (dst);
}
