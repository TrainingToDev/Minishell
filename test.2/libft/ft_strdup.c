/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:48:03 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/01 11:53:04 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	size_t	size;
	size_t	i;
	char	*dest;

	size = ft_strlen(str);
	i = 0;
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (0);
	while (i < size)
	{
		dest[i] = ((char *)str)[i];
		i++;
	}
	dest[i] = '\0';
	return ((char *)dest);
}
