/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:27:11 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/10 12:54:38 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parsing.h"

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

static int	already_existing_room(t_room *list, t_room *element)
{
	t_room	*temp;

	temp = list;
	while (temp != NULL)
	{
		if (ft_strcmp(element->name, temp->name) == 0)
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

t_room	*push_front(t_room *list, t_room *element)
{
	if (already_existing_room(list, element))
		return (NULL);
	if (element == NULL)
		return (NULL);
	if (list == NULL)
		return (element);
	element->next = list;
	return (element);
}
