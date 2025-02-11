/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 04:18:42 by herandri          #+#    #+#             */
/*   Updated: 2024/03/25 07:08:26 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str_join;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_join = (char *) ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!str_join)
		return (NULL);
	ft_memcpy(str_join, s1, s1_len);
	ft_memcpy(str_join + s1_len, s2, s2_len);
	return (str_join);
}
