/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:03:28 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/10 13:11:12 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*stock;

	if (!lst)
		return ;
	while (*lst)
	{
		stock = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = stock;
	}
}
