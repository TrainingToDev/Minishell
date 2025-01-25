/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 03:03:19 by herandri          #+#    #+#             */
/*   Updated: 2024/03/25 07:15:54 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace_is_no_printable(int c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (ft_isspace_is_no_printable(*nptr))
		nptr++;
	if (*nptr == '+' && *(nptr + 1) != '-')
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		result *= 10;
		result += *nptr - 48;
		nptr++;
	}
	result *= sign;
	return (result);
}
