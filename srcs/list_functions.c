/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:32:51 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/05 18:32:53 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TODO change this so that if list is not initialized it becomes the new el
void	lst_add_back(t_void_list *list, t_void_list *new)
{
	if (list && new)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

void	lst_add_back2(t_void_list **list, t_void_list *new)
{
	t_void_list *ptr;

	if (new)
	{
		if (!(*list))
			*list = new;
		else
		{
			ptr = *list;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new;
		}
	}
}

size_t	get_list_size(t_void_list *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	remove_from_list(t_void_list **list, t_void_list *node, t_void_list *prev)
{
	if (!prev)
		*list = node->next;
	else
		prev->next = node->next;
}
