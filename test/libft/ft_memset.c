/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:25 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/04 12:14:18 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t size)
{
	char	*strs;
	size_t	i;

	i = 0;
	strs = (char *)str;
	while (i < size)
	{
		strs[i] = (char)c;
		i++;
	}
	return (strs);
}
