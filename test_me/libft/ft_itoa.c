/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 04:10:43 by herandri          #+#    #+#             */
/*   Updated: 2024/03/25 07:06:55 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countdigit_in_nbr(int nbr)
{
	int	length;

	length = 0;
	if (nbr < 1)
		length++;
	while (nbr)
	{
		nbr = nbr / 10;
		length++;
	}
	return (length);
}

static char	*ft_newstr(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

static int	ft_abs_value(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				sign;
	char			*ptr;
	char			*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	str = ft_newstr(ft_countdigit_in_nbr(n));
	if (!str)
		return (NULL);
	ptr = str + ft_countdigit_in_nbr(n);
	*ptr = '\0';
	nbr = ft_abs_value(n);
	while (ptr != str)
	{
		*(--ptr) = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	if (sign)
		*ptr = '-';
	return (str);
}
