/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:09:52 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/04 11:12:20 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_int(long n)
{
	int	c;

	c = 1;
	if (n < 0)
	{
		c = 2;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

static char	*transform(int n, char *nb)
{
	size_t	i;
	size_t	sign;
	long	a;

	i = 0;
	a = (long)n;
	sign = 0;
	if (a < 0)
	{
		a *= -1;
		sign = 1;
	}
	while (a != 0)
	{
		nb[i] = a % 10 + 48;
		a = a / 10;
		i++;
	}
	if (sign == 1)
		nb[i++] = '-';
	nb[i] = '\0';
	return (nb);
}

static char	*reverse(int n, char *nb)
{
	size_t	i;
	size_t	len;
	char	swap;

	i = 0;
	nb = (char *)malloc(sizeof(char) * (count_int((long)n) + 1));
	if (!nb)
		return (NULL);
	nb = transform(n, nb);
	len = ft_strlen((const char *)nb);
	while (len > i)
	{
		len--;
		swap = nb[i];
		nb[i] = nb[len];
		nb[len] = swap;
		i++;
	}
	nb[2 * i + 1] = '\0';
	return (nb);
}

char	*ft_itoa(int n)
{
	char	*nb;

	if (n == 0)
	{
		nb = (char *)malloc(sizeof(char) * 2);
		if (!nb)
			return (NULL);
		*nb = '0';
		*(nb + 1) = '\0';
		return (nb);
	}
	nb = NULL;
	nb = reverse(n, nb);
	return (nb);
}
