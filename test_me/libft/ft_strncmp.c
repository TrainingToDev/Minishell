/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:52:18 by herandri          #+#    #+#             */
/*   Updated: 2024/03/21 10:46:51 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*check_s1;
	unsigned char	*check_s2;

	check_s1 = (unsigned char *) s1;
	check_s2 = (unsigned char *) s2;
	while ((*check_s1 || *check_s2) && n--)
	{
		if (*check_s1 != *check_s2)
			return (*check_s1 - *check_s2);
		check_s1++;
		check_s2++;
	}
	return (0);
}
