/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:27:11 by mde-maul          #+#    #+#             */
/*   Updated: 2022/08/01 18:27:13 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	push_front_node(t_path_node **path, t_path_node *path_node)
{
	if (path && path_node)
	{
		path_node->next = *path;
		*path = path_node;
	}
}

void	lst_add_in_order(t_paths **paths, t_paths *path_el)
{
	t_paths	*ptr;
	t_paths	*prev;

	if (!(*paths))
		*paths = path_el;
	else
	{
		ptr = *paths;
		prev = NULL;
		while (ptr && path_el->path_size > ptr->path_size)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		if (!prev)
		{
			path_el->next = ptr;
			*paths = path_el;
		}
		else
		{
			path_el->next = ptr;
			prev->next = path_el;
		}
	}
}
