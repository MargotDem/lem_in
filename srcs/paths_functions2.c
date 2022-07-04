/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:35:44 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/05 18:35:49 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths	*create_path_el()
{
	t_paths	*path_el;

	path_el = (t_paths *)malloc(sizeof(t_paths));
	if (!path_el)
		handle_error();
	path_el->next = NULL;
	path_el->path = NULL;
	path_el->path_size = 0;
	path_el->nb_ants = 0;
	path_el->nb_ants2 = 0;
	path_el->ants = NULL;
	return (path_el);
}

void	add_path_to_list(t_paths **all_paths, t_room **history)
{
	size_t		j;
	t_paths		*path_el;
	t_path_node	*path_node;

	path_el = create_path_el();
	j = 0;
	while (history[j])
	{
		path_node = (t_path_node *)malloc(sizeof(t_path_node));
		if (!path_node)
			handle_error();
		path_node->next = NULL;
		path_node->node = history[j];
		if (!path_el->path)
			path_el->path = path_node;
		else
			lst_add_back((t_void_list *)path_el->path, (t_void_list *)path_node);
		j++;
	}
	if (!(*all_paths))
		*all_paths = path_el;
	else
		lst_add_back((t_void_list *)*all_paths, (t_void_list *)path_el);
}

void	find_all_paths(t_room *node, t_paths **all_paths, t_room **history)
{
	size_t	nb_links;
	t_room	**links;
	size_t	i;

	// TODO change this to real end
	if (strings_match(node->name, "end"))
	{
		add_path_to_list(all_paths, history);
		return ;
	}
	nb_links = node->nb_links;
	links = node->links;
	i = 0;
	while (i < nb_links)
	{
		if (not_in_history(links[i], history))
		{
			push_history(history, links[i]);
			find_all_paths(links[i], all_paths, history);
			pop_history(history);
		}
		i++;
	}
}

int		paths_intersect(t_path_node *path1, t_path_node *path2)
{
	t_path_node	*path;

	while (path1)
	{
		path = path2;
		while (path)
		{
			// TODO replace start and end with actual start and end room names
			if (strings_match(path->node->name, path1->node->name) && \
				(!strings_match(path->node->name, "start") && \
				(!strings_match(path->node->name, "end"))))
				return (1);
			path = path->next;
		}
		path1 = path1->next;
	}
	return (0);
}

void	remove_intersecting_paths(t_paths **all_paths, t_paths *shortest)
{
	t_paths	*prev;
	t_paths	*cur;
	t_paths	*next;

	prev = NULL;
	cur = *all_paths;
	while (cur)
	{
		next = cur->next;
		if (paths_intersect(cur->path, shortest->path))
		{
			remove_from_list((t_void_list **)all_paths, (t_void_list *)cur, (t_void_list *)prev);
			// free the list cur->path
			// free cur
		}
		else
			prev = cur;
		cur = next;
	}
}

void	get_shortest(t_paths *all_paths, t_paths **shortest_and_prev)
{
	t_paths	*t_paths_ptr;
	t_paths	*shortest;
	t_paths	*shortest_prev;
	t_paths	*prev;
	size_t	shortest_size;

	t_paths_ptr = all_paths;
	shortest = t_paths_ptr;
	shortest_prev = NULL;
	prev = NULL;
	shortest_size = get_list_size((t_void_list *)shortest->path);
	while (t_paths_ptr)
	{
		if (get_list_size((t_void_list *)t_paths_ptr->path) < shortest_size)
		{
			shortest = t_paths_ptr;
			shortest_prev = prev;
		}
		prev = t_paths_ptr;
		t_paths_ptr = t_paths_ptr->next;
	}
	shortest_and_prev[0] = shortest;
	shortest_and_prev[1] = shortest_prev;
}

int	paths_intersect_with_shortest(t_paths *all_paths, t_paths *shortest)
{
	size_t	nb_intersecting;

	nb_intersecting = 0;
	while (all_paths)
	{
		if (paths_intersect(shortest->path, all_paths->path))
			nb_intersecting++;
		all_paths = all_paths->next;
	}
	if (nb_intersecting < 2)
		return (0);
	return (1);
}

void	select_optimal_paths(t_paths *all_paths, t_paths **optimal_paths, size_t nb_ants)
{
	t_paths	*shortest;
	t_paths	*shortest_prev;
	t_paths	*shortest_and_prev[2];
	t_paths *all_paths_copy;
	t_paths *optimal_paths_copy;
	t_paths *ptr;

	all_paths_copy = NULL;
	optimal_paths_copy = NULL;
	if (!all_paths) // is this necessary
		return ;
	get_shortest(all_paths, shortest_and_prev);
	shortest = shortest_and_prev[0];
	shortest_prev = shortest_and_prev[1];
	remove_from_list((t_void_list **)&all_paths, (t_void_list *)shortest, (t_void_list *)shortest_prev);

	shortest->next = NULL;

	if (paths_intersect_with_shortest(all_paths, shortest))
	{
		//copy all paths and optimal paths
		copy_path(all_paths, &all_paths_copy);
		copy_path(*optimal_paths, &optimal_paths_copy);

		// simulation one:
		select_optimal_paths(all_paths, optimal_paths, nb_ants);
		distribute_ants(*optimal_paths, nb_ants);

		// simulation of the alternative
		// add shortest to optimal paths copy
		if (!optimal_paths_copy)
			optimal_paths_copy = shortest;
		else
			lst_add_back((t_void_list *)optimal_paths_copy, (t_void_list *)shortest);

		remove_intersecting_paths(&all_paths_copy, shortest);
		select_optimal_paths(all_paths_copy, &optimal_paths_copy, nb_ants);
		distribute_ants(optimal_paths_copy, nb_ants);

		if (optimal_paths_copy->path_size + optimal_paths_copy->nb_ants <= (*optimal_paths)->path_size + (*optimal_paths)->nb_ants)
		{
			// free optimal paths 
			*optimal_paths = optimal_paths_copy;
		}			
		// reset nb ants
		ptr = *optimal_paths;
		while (ptr)
		{
			ptr->nb_ants = 0;
			ptr = ptr->next;
		}
	}
	else
	{
		// add shortest to optimal paths list
		if (!(*optimal_paths))
			*optimal_paths = shortest;
		else
			lst_add_back((t_void_list *)*optimal_paths, (t_void_list *)shortest);
		remove_intersecting_paths(&all_paths, shortest);
		select_optimal_paths(all_paths, optimal_paths, nb_ants);
	}
}

void	find_optimal_paths(t_room *graph, t_paths **optimal_paths, size_t nb_ants)
{
	t_paths	*all_paths;
	t_room	*history[100];

	reset_history(history);
	push_history(history, graph);
	all_paths = NULL;
	find_all_paths(graph, &all_paths, history);
	select_optimal_paths(all_paths, optimal_paths, nb_ants);
}
