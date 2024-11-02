/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herandri <herandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:19:04 by herandri          #+#    #+#             */
/*   Updated: 2024/03/25 07:07:14 by herandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_element;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		next_element = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_element;
	}
	free(*lst);
	*lst = NULL;
}
