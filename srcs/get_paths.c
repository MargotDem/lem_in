/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:33:04 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/10 12:35:01 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	create_path_node(t_path_node **path_node, t_room *node)
{
	(*path_node) = (t_path_node *)(malloc(sizeof(t_path_node)));
	if (!(*path_node))
		return (ERROR);
	(*path_node)->next = NULL;
	(*path_node)->node = node;
	return (OK);
}

int	get_path(t_room *node, t_paths **paths, t_room *graph, t_room *end)
{
	t_paths			*path_el;
	t_path_node		*path_node;
	size_t			path_size;

	path_el = create_path_el();
	if (!path_el)
		return (ERROR);
	path_size = 2;
	if (!create_path_node(&path_node, end))
		return (ERROR);
	path_el->path = path_node;
	while (node && node != graph)
	{
		path_size++;
		if (!create_path_node(&path_node, node))
			return (ERROR);
		push_front_node(&(path_el->path), path_node);
		node = node->reverse;
	}
	if (!create_path_node(&path_node, graph))
		return (ERROR);
	push_front_node(&(path_el->path), path_node);
	path_el->path_size = path_size;
	if (!(*paths))
		(*paths) = path_el;
	else
		lst_add_in_order(paths, path_el);
	return (OK);
}

void	get_paths(t_vector *all_paths_combos, \
	t_room *graph, t_data *data)
{
	unsigned int	i;
	t_room			*end;
	t_paths			*paths;

	i = 0;
	end = search_for(data->end_room_name, data);
	paths = NULL;
	while (i < end->total_links)
	{
		if (end->links[i]->reverse)
			if (!get_path(end->links[i], &paths, graph, end))
				exit_solver(all_paths_combos, data);
		i++;
	}
	push_to_vect(all_paths_combos, paths);
}
