/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:08:21 by emichels          #+#    #+#             */
/*   Updated: 2023/11/16 16:52:47 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*new;
	void	*temp;

	new = NULL;
	while (lst)
	{
		temp = (*f)(lst->content);
		map = ft_lstnew(temp);
		if (!map)
		{
			del(temp);
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, map);
		lst = lst->next;
	}
	return (new);
}
