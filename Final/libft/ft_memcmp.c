/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:53:22 by herandri          #+#    #+#             */
/*   Updated: 2024/03/21 10:27:59 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*check_s1;
	unsigned char	*check_s2;

	check_s1 = (unsigned char *) s1;
	check_s2 = (unsigned char *) s2;
	while (n > 0)
	{
		if (*check_s1 != *check_s2)
		{
			return (*check_s1 - *check_s2);
		}
		check_s1++;
		check_s2++;
		n--;
	}
	return (0);
}
