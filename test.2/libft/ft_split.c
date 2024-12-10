/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:38:39 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/01 11:45:34 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count(char const *s, char c)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			n++;
		}
	}
	return (n);
}

static unsigned int	count_len(const char *s, char c, size_t i)
{
	size_t	a;

	a = i;
	while (s[i])
	{
		if (s[i] == c)
			return (i - a);
		i++;
	}
	return (i - a);
}

static void	ft_free(char **dest, size_t len)
{
	while (0 < len)
	{
		free(*dest + len);
		len--;
	}
	free(dest);
}

static char	**ft_array(char **dest, const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < count(s, c))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		*(dest + j) = ft_substr(s, i, count_len(s, c, i));
		if (!(dest + j))
		{
			ft_free(dest, j);
		}
		while (*(s + i) && *(s + i) != c)
			i++;
		j++;
	}
	*(dest + j) = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
	{
		dest = (char **)malloc(sizeof(char));
		*dest = NULL;
		return (dest);
	}
	dest = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!dest)
		return (NULL);
	dest = ft_array(dest, s, c);
	return (dest);
}
