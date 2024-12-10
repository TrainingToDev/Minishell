/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:24:14 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/03 16:29:09 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	ft_len;
	char	*dest;

	ft_len = ft_strlen(s);
	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_len)
		return (ft_strdup(""));
	if (len >= (ft_len - start))
		len = (ft_len - start);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (0);
	while (i < len)
	{
		dest[i] = ((char *)s)[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
