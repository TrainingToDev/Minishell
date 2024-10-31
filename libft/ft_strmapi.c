/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 04:08:14 by herandri          #+#    #+#             */
/*   Updated: 2024/03/25 07:08:39 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out_s;
	unsigned int	i;
	size_t			slen;

	if (!s || !f)
		return (NULL);
	slen = ft_strlen(s);
	out_s = ft_calloc((slen + 1), sizeof(char));
	if (!out_s)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		out_s[i] = f(i, s[i]);
		i++;
	}
	out_s[i] = '\0';
	return (out_s);
}
