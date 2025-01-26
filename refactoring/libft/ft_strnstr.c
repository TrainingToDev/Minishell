/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:54:37 by herandri          #+#    #+#             */
/*   Updated: 2024/03/25 07:08:45 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_match(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len > len)
		return (0);
	if (ft_strncmp(big + 1, little, little_len) == 0)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	c;

	c = *little++;
	if (c != '\0')
	{
		while (len-- >= 1)
		{
			if (*big != '\0')
			{
				if (*big == c && check_match(big, little, len))
					return ((char *) big);
				big++;
			}
			else
				return (NULL);
		}
		return (NULL);
	}
	return ((char *) big);
}
