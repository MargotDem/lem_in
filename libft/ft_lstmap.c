/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:22:35 by mde-maul          #+#    #+#             */
/*   Updated: 2021/11/04 13:22:38 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del(void *ptr, size_t n)
{
	(void)n;
	free(ptr);
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list_el;
	t_list	*new_list;
	t_list	*new_list_start;

	if (!f || !lst)
		return (NULL);
	new_list = f(ft_lstnew(lst->content, lst->content_size));
	if (!new_list)
		return (NULL);
	new_list_start = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list_el = f(ft_lstnew(lst->content, lst->content_size));
		if (!new_list_el)
		{
			ft_lstdel(&new_list_start, &del);
			return (NULL);
		}
		new_list->next = new_list_el;
		new_list = new_list_el;
		lst = lst->next;
	}
	return (new_list_start);
}
