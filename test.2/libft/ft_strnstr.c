/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:09:51 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/03 12:09:00 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i;
	size_t	c;

	i = 0;
	if (find[0] == '\0')
		return ((char *)str);
	while (i < n && str[i] != '\0')
	{
		c = 0;
		while (find[c] != '\0' && (i + c) < n)
		{
			if (find[c] != str[i + c])
				break ;
			c++;
		}
		if (find[c] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
