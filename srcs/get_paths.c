/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:33:04 by mde-maul          #+#    #+#             */
/*   Updated: 2022/08/05 08:56:40 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_path_node(t_path_node **path_node, t_room *node)
{
	(*path_node) = (t_path_node *)handle_null(malloc(sizeof(t_path_node)));
	printf("(*path_node: %p\n)", (*path_node));
	(*path_node)->next = NULL;
	(*path_node)->node = node;
}

void	get_path(t_room *node, t_paths **paths, t_room *graph, t_room *end)
{
	t_paths			*path_el;
	t_path_node		*path_node;
	size_t			path_size;

	path_el = create_path_el();
	path_size = 2;
	create_path_node(&path_node, end);
	path_el->path = path_node;
	while (node && node != graph)
	{
		path_size++;
		create_path_node(&path_node, node);
		push_front_node(&(path_el->path), path_node);
		node = node->reverse;
	}
	if (node != graph)
		ft_putstr("ALERT so here we have a path that ends \
			with a node other than start, this should NEVER happen\n");
	create_path_node(&path_node, graph);
	push_front_node(&(path_el->path), path_node);
	path_el->path_size = path_size;
	if (!(*paths))
		(*paths) = path_el;
	else
		lst_add_in_order(paths, path_el);
}

void	get_paths(t_all_paths_combos *all_paths_combos, \
	t_room *graph, t_data *data)
{
	unsigned int				i;
	t_room			*end;
	t_paths			*paths;

	i = 0;
	end = search_for(data->end_room_name, data);
	paths = NULL;
	while (i < end->total_links)
	{
		if (end->links[i]->reverse)
			get_path(end->links[i], &paths, graph, end);
		i++;
	}
	all_paths_combos->arr[all_paths_combos->counter] = paths;
	all_paths_combos->counter++;
}
