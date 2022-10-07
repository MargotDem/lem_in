/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_start_to_end_path.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:07:10 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/07 11:00:41 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	end_connected_to_start(t_room *start, t_data *data)
{
	int	connected;
	int	i;

	connected = 0;
	i = 0;
	while (i < (int)start->total_links)
	{
		if (strings_match((start->links[i])->name, data->end_room_name))
			return (1);
		i++;
	}
	return (0);
}

int	create_start_end_path(t_paths **path, t_room *start, t_room *end)
{
	t_path_node		*node;

	(*path) = create_path_el();
	if (!path)
		return (ERROR);
	(*path)->path_size = 2;
	if (!create_path_node(&node, end))
		return (ERROR);
	(*path)->path = node;
	if (!create_path_node(&node, start))
		return (ERROR);
	push_front_node(&((*path)->path), node);
	return (OK);
}

void	handle_start_to_end_path(t_room *graph, t_data *data, \
	t_vector *all_paths_combos)
{
	t_paths			*path;
	t_room			*end;

	if (end_connected_to_start(graph, data))
	{
		end = search_for(data->end_room_name, data);
		if (!create_start_end_path(&path, graph, end))
			exit_solver(all_paths_combos, data);
		push_to_vect(all_paths_combos, path);
	}
}

void	handle_start_to_end_path2(t_room *graph, t_data *data, \
	t_vector *all_paths_combos)
{
	t_paths		*path;
	t_room		*end;
	size_t		i;

	if (end_connected_to_start(graph, data))
	{
		i = 1;
		end = search_for(data->end_room_name, data);
		while (i < all_paths_combos->counter)
		{
			if (!create_start_end_path(&path, graph, end))
				exit_solver(all_paths_combos, data);
			path->next = (all_paths_combos->arr[i]);
			(all_paths_combos->arr[i]) = path;
			i++;
		}
	}
}
