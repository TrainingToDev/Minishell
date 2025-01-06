/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:49:59 by herandri          #+#    #+#             */
/*   Updated: 2024/03/05 15:02:26 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*last_occ;

	str = (char *) s;
	last_occ = NULL;
	while (1)
	{
		if (*str == (unsigned char) c)
		{
			last_occ = str;
		}
		if (*str == '\0')
		{
			break ;
		}
		str++;
	}
	return (last_occ);
}
