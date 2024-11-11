/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:17:58 by miaandri          #+#    #+#             */
/*   Updated: 2024/03/10 13:45:23 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*result;

	if (!lst)
		return (NULL);
	res = ft_lstnew((f)(lst->content));
	result = res;
	lst = lst->next;
	while (lst)
	{
		res = ft_lstnew((f)(lst->content));
		if (!res)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&result, res);
	}
	return (result);
}
