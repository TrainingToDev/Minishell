/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:01:43 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/01 11:21:28 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*cast;

	i = 0;
	cast = (char *)str;
	while (i < n)
	{
		cast[i] = '\0';
		i++;
	}
	return ((void *)cast);
}
