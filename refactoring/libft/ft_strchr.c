/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:48:13 by herandri          #+#    #+#             */
/*   Updated: 2024/03/21 10:03:37 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	check_c;

	check_c = c;
	while (*s)
	{
		if (*s == check_c)
			return ((char *) s);
		s++;
	}
	if (*s == check_c)
		return ((char *) s);
	else
		return (NULL);
}
