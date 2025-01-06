/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:13:21 by herandri          #+#    #+#             */
/*   Updated: 2024/03/09 17:21:08 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

static	int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
