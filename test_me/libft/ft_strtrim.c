/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 04:16:12 by herandri          #+#    #+#             */
/*   Updated: 2024/03/25 07:09:00 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_checkchar(char const *str, char const c)
{
	const char	*ptr;

	if (!str)
		return (0);
	ptr = str;
	while (*ptr)
	{
		if (*ptr == c)
			return (1);
		ptr++;
	}
	return (0);
}

static char	*ft_newstr(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trimmed_str;
	const char	*from;
	const char	*to;
	char		*ptr;

	if (!s1 || !set)
		return (NULL);
	from = s1;
	while (*from && ft_checkchar(set, *from))
		from++;
	to = s1 + ft_strlen(s1);
	while (to > from && ft_checkchar(set, *(to - 1)))
		to--;
	trimmed_str = ft_newstr(to - from);
	if (!trimmed_str)
		return (NULL);
	ptr = trimmed_str;
	while (from < to)
	{
		*ptr = *from;
		ptr++;
		from++;
	}
	*ptr = '\0';
	return (trimmed_str);
}
