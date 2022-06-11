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

void	add_path_to_list(t_paths **all_paths, t_graph **history)
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

void	find_all_paths(t_graph *node, t_paths **all_paths, t_graph **history)
{
	size_t	nb_links;
	t_graph	**links;
	size_t i;

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

t_paths	*copy_paths_node(t_paths *node)
{
	t_paths	*new;

	new = (t_paths *)malloc(sizeof(t_paths));
	// if null

	new->next = NULL;
	new->path = node->path;
	new->path_size = node->path_size;
	new->nb_ants = node->nb_ants;
	new->nb_ants2 = node->nb_ants2;

	return (new);
}

int	shortest_is_optimal(t_paths *all_paths, t_paths *shortest, size_t nb_ants)
{
	size_t	nb_turns_shortest;
	size_t	nb_turns_alternative;
	t_paths	*intersecting_paths;
	t_paths	*alternative_paths;
	t_paths	*new;
	size_t	nb_intersecting;

	nb_intersecting = 0;
	intersecting_paths = NULL;
	alternative_paths = NULL;
	nb_turns_shortest = get_path_node_size(shortest->path) + nb_ants - 2;
	// find out all the paths that intersect with shortest, create a linked list with them: intersecting_paths
	while (all_paths)
	{
		//printf("here\n");
		if (paths_intersect(shortest->path, all_paths->path))
		{
			nb_intersecting++;
			new = copy_paths_node(all_paths);
			if (!intersecting_paths)
				intersecting_paths = new;
			else
				lst_add_back((t_void_list *)intersecting_paths, (t_void_list *)new);
		}
		all_paths = all_paths->next;
	}
	if (nb_intersecting < 2)
		return (1);
	select_optimal_paths(intersecting_paths, &alternative_paths, nb_ants);
	distribute_ants(alternative_paths, nb_ants);
	nb_turns_alternative = alternative_paths->path_size + alternative_paths->nb_ants - 2;
	if (nb_turns_shortest <= nb_turns_alternative)
		return (1);
	return (0);
	// FREE EVERYTHINGGGG
}

void	update_all_paths(t_paths **all_paths, t_paths *shortest)
{
	t_paths	*prev;
	t_paths	*cur;

	prev = NULL;
	cur = *all_paths;
	while (cur)
	{
		if (paths_intersect(cur->path, shortest->path))
		{
			// remove cur from all_paths
			if (!prev)
				*all_paths = cur->next;
			else
				prev->next = cur->next;
		}
		else
			prev = cur;
		cur = cur->next;
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
	shortest_size = get_path_node_size(shortest->path);
	while (t_paths_ptr)
	{
		if (get_path_node_size(t_paths_ptr->path) < shortest_size)
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

void	select_optimal_paths(t_paths *all_paths, t_paths **optimal_paths, size_t nb_ants)
{
	t_paths	*shortest;
	t_paths	*shortest_prev;
	t_paths	*shortest_and_prev[2];

	while (all_paths)
	{
		get_shortest(all_paths, shortest_and_prev);
		shortest = shortest_and_prev[0];
		shortest_prev = shortest_and_prev[1];

		// take shortest out of the all_paths list
		if (!shortest_prev)
			all_paths = shortest->next;
		else
			shortest_prev->next = shortest->next;
		shortest->next = NULL;

		// if shortest is not optimal, start again, to find the next shortest
		if (!shortest_is_optimal(all_paths, shortest, nb_ants))
			continue ;

		// otherwise, add shortest to shortest paths list
		if (!(*optimal_paths))
			*optimal_paths = shortest;
		else
			lst_add_back((t_void_list *)*optimal_paths, (t_void_list *)shortest);

		// take the paths that intersect with shortest out of the all paths list.
		// this is what ultimately breaks us out of the while loop
		update_all_paths(&all_paths, shortest);
	}
}
	/* by the grace of God the previous code seems to work but i dont actually trust it, so keeping this here just in case
	yes its bad practice
	no i wont stop doing it
	while (1)
	{
		// search shortest
		reset_history(history);
		push_history(history, graph);
		potential_paths = NULL;
		find_all_paths(graph, &potential_paths, history, paths);
		if (!potential_paths)
			break ;
		t_paths_ptr = potential_paths;
		// !!!! if nulll
		shortest = t_paths_ptr;
		shortest_size = get_path_node_size(shortest->path);
		while (t_paths_ptr)
		{
			if (get_path_node_size(t_paths_ptr->path) < shortest_size)
				shortest = t_paths_ptr;
			t_paths_ptr = t_paths_ptr->next;
		}

		// copy_path(shortest, &shortest_copy);
		// instead of doing this, dont forget to free the other ones from potential paths ie up until shortest and after shortest
		shortest->next = NULL;
		shortest->nb_ants = 0;

		// from all the potential paths, find the shortest one and add it to paths linked list
		if (!(*paths))
			*paths = shortest;
		else
			lst_add_back((t_void_list *)*paths, (t_void_list *)shortest);
	}
*/

void	find_optimal_paths(t_graph *graph, t_paths **optimal_paths, size_t nb_ants)
{
	t_paths	*all_paths;
	t_graph	*history[100];

	reset_history(history);
	push_history(history, graph);
	all_paths = NULL;
	find_all_paths(graph, &all_paths, history);
	select_optimal_paths(all_paths, optimal_paths, nb_ants);
}
