/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:33:04 by mde-maul          #+#    #+#             */
/*   Updated: 2022/08/01 18:33:07 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_paths(t_all_paths_combos *all_paths_combos, t_room *graph, t_data *data)
{
	int	i;
	int	j;
	t_room	*end;
	t_room	*node;
	t_paths *path_el;
	t_paths *paths;
	t_path_node *path_node;
	size_t	path_size;

	i = 0;
	paths = NULL;
	end = search_for(data->exit_room, data);
	while (i < end->nb_links)
	{
		if (end->links[i]->reverse)
		{
			path_el = create_path_el();
			path_size = 2;
			path_node = (t_path_node *)malloc(sizeof(t_path_node));
			if (!path_node)
				handle_error();
			path_node->next = NULL;
			path_node->node = end;
			path_el->path = path_node;
			j = 0;
			node = end->links[i];
			while (node && node != graph)
			{
				path_size++;
				path_node = (t_path_node *)malloc(sizeof(t_path_node));
				if (!path_node)
					handle_error();
				path_node->next = NULL;
				path_node->node = node;
				push_front(&(path_el->path), path_node);
				node = node->reverse;
			}
			if (node != graph)
				ft_putstr("ALERT so here we have a path that ends with a node other than start, this should NEVER happen\n");
			path_node = (t_path_node *)malloc(sizeof(t_path_node));
			if (!path_node)
				handle_error();
			path_node->next = NULL;
			path_node->node = graph;
			push_front(&(path_el->path), path_node);
			path_el->path_size = path_size;
			if (!paths)
				paths = path_el;
			else
				lst_add_in_order(&paths, path_el);
		}
		i++;
	}
	all_paths_combos->arr[all_paths_combos->counter] = paths;
	all_paths_combos->counter++;
}
