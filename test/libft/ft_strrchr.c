/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:15:52 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/03 11:07:33 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = (int)ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == (char)c)
		{
			return ((char *)str + len);
		}
		len--;
	}
	return (NULL);
}
