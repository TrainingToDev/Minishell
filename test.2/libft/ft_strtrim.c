/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:45:14 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/03 17:04:11 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in(char const s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (s1 != set[i])
			i++;
		else
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	n;
	char	*dest;

	i = 0;
	len = ft_strlen(s1);
	n = 0;
	if (!s1 || !set)
		return (0);
	while (s1[i] && in(s1[i], set) == 1)
		i++;
	while (in(s1[len - 1], set) == 1 && len > i)
		len--;
	dest = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!dest)
		return (0);
	while (i < len)
	{
		dest[n] = s1[i];
		i++;
		n++;
	}
	dest[n] = '\0';
	return (dest);
}
