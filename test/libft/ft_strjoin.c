/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:04:51 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/11 12:17:23 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*dest;

	i = 0;
	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!dest)
		return (0);
	while (i < len1)
	{
		dest[i] = ((char *)s1)[i];
		i++;
	}
	while (i - len1 < len2)
	{
		dest[i] = ((char *)s2)[i - len1];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
