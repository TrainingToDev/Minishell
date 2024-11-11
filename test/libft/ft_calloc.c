/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:46:01 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/01 11:22:33 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(unsigned int len, size_t size)
{
	size_t	i;
	void	*str;

	i = 0;
	if (len * size > 2147483647)
		return (0);
	else
	{
		str = (void *)malloc((size * len));
		if (!str)
			return (0);
		while (i < (size * len))
		{
			((char *)str)[i] = 0;
			i++;
		}
		return ((void *)str);
	}
}
