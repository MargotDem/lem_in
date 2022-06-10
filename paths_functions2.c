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

void	find_potential_paths(t_graph *node, t_paths **potential_paths, t_graph **history, t_paths **paths)
{
	size_t	nb_links;
	t_graph	**links;
	t_graph	*link;
	size_t i;
	

	nb_links = node->nb_links;
	links = node->links;
	if (strings_match(node->name, "end"))
	{
		// add the history plus end to the potential paths linked list
		
		size_t j;
		j = 0;
		t_paths	*path_el;
		t_path	*node;
		t_path	*path;
	
		path_el = (t_paths *)malloc(sizeof(t_paths));
		//if !
		path_el->next = NULL;
		path_el->path = NULL;
		path_el->path_size = 0;

		path = NULL;
		while (history[j])
		{
			node = (t_path *)malloc(sizeof(t_path));
			//if !
			node->next = NULL;
			node->node = history[j];
			if (!path)
				path = node;
			else
				lst_add_back((t_void_list *)path, (t_void_list *)node);
			j++;
		}
		path_el->path = path;
		if (!(*potential_paths))
			*potential_paths = path_el;
		else
			lst_add_back((t_void_list *)*potential_paths, (t_void_list *)path_el);
		return ;
	}
	i = 0;
	
	while (i < nb_links)
	{
		link = links[i];
		if (not_in_history(link, history) && not_in_paths(link, paths))
		{
			push_history(history, link);
			find_potential_paths(link, potential_paths, history, paths);
			pop_history(history);
		}
		i++;
	}
}

int		paths_intersect(t_path *path1, t_path *path2)
{
	t_path	*path;

	while (path1)
	{
		path = path2;
		while (path)
		{
			if (strings_match(path->node->name, path1->node->name) && (!strings_match(path->node->name, "start") && (!strings_match(path->node->name, "end"))))
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

int	shortest_optimal(t_paths *all_paths, t_paths *shortest, size_t nb_ants)
{
	size_t	nb_turns_shortest;
	size_t	nb_turns_alternative;
	t_paths	*intersecting_paths;
	t_paths	*alternative_paths;
	t_paths	*new;
	size_t	nb_intersecting;

	nb_intersecting = 0;
	intersecting_paths = NULL;
	(void)new;
	(void)alternative_paths;
	alternative_paths = NULL;
	nb_turns_shortest = get_path_size(shortest->path) + nb_ants - 2;
	printf("nb turns shortest is %zu\n", nb_turns_shortest);

	// find out all the paths that intersect with shortest, create a linked list with them: intersecting_paths
	// of course, skip shortest in all_paths
	while (all_paths)
	{
		//printf("here\n");
		if (shortest != all_paths && paths_intersect(shortest->path, all_paths->path))
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
	{
		printf("less than 2 intersecting: %zu\n", nb_intersecting);
		printf("\n");
		return (1);
	}
	printf("\n");
	
	// 
	select_optimal_paths(intersecting_paths, &alternative_paths, nb_ants);
	distribute_ants(alternative_paths, nb_ants);
	printf("HEREEEE\n");
	print_paths(alternative_paths);
	printf("HEREEEE\n");
	nb_turns_alternative = alternative_paths->path_size + alternative_paths->nb_ants - 2;

	printf("nb turns shortest is %zu, and alternative is %zu\n", nb_turns_shortest, nb_turns_alternative);
	printf("intersecting path path size is  %zu, and intersectin path nb ants is %zu\n", alternative_paths->path_size, alternative_paths->nb_ants);
	if (nb_turns_shortest <= nb_turns_alternative)
	{
		
		return (1);
	}
	printf("so NOPEEE\n");
	return (0);
	//return (0) en theorie mais lets see;

	// FREE EVERYTHINGGGG
}

void	update_all_paths(t_paths **all_paths, t_paths *shortest)
{
	t_paths	*prev;
	t_paths	*cur;
	t_paths	*next;
	
//	t_path	*shortest_path;

	prev = NULL;
	cur = *all_paths;
	next = NULL;
	while (cur)
	{
		if (paths_intersect(cur->path, shortest->path))
		{
			// remove cur from all_paths
			if (!prev)
			{
				*all_paths = cur->next;
			}
			else
			{
				prev->next = cur->next;
			}
		}
		else
		{
			prev = cur;
			//next = cur->next;
		}
		cur = cur->next;
	}
}

void	select_optimal_paths(t_paths *all_paths, t_paths **paths, size_t nb_ants)
{
	t_paths	*t_paths_ptr;
	t_paths	*shortest;
	t_paths	*shortest_prev;
	t_paths	*prev;
	size_t	shortest_size;

	while (all_paths)
	{
		t_paths_ptr = all_paths;
		// !!!! if nulll
		shortest = t_paths_ptr;
		shortest_prev = NULL;
		prev = NULL;
		shortest_size = get_path_size(shortest->path);
		while (t_paths_ptr)
		{
			if (get_path_size(t_paths_ptr->path) < shortest_size)
			{
				shortest = t_paths_ptr;
				shortest_prev = prev;
			}
			prev = t_paths_ptr;
			t_paths_ptr = t_paths_ptr->next;
		}

		// if shortest is not optimal, yeet it out of the list and start again
		// else, do the following
		if (!shortest_optimal(all_paths, shortest, nb_ants))
		{
			// take shortest out of the all_paths list
			if (!shortest_prev)
				all_paths = shortest->next;
			else
				shortest_prev->next = shortest->next;
			continue ;
		}

		// take shortest out of the all_paths list
		if (!shortest_prev)
			all_paths = shortest->next;
		else
			shortest_prev->next = shortest->next;
		
		shortest->next = NULL;
		shortest->nb_ants = 0; // this is necessary. don't ask why

		// add shortest to shortest paths list
		if (!(*paths))
			*paths = shortest;
		else
			lst_add_back((t_void_list *)*paths, (t_void_list *)shortest);

		// take the paths that intersect with shortest out of the all paths list.
		// this is what ultimately breaks us out of the while loop
		update_all_paths(&all_paths, shortest);
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
		find_potential_paths(graph, &potential_paths, history, paths);
		if (!potential_paths)
			break ;
		t_paths_ptr = potential_paths;
		// !!!! if nulll
		shortest = t_paths_ptr;
		shortest_size = get_path_size(shortest->path);
		while (t_paths_ptr)
		{
			if (get_path_size(t_paths_ptr->path) < shortest_size)
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
}

void	find_optimal_paths(t_graph *graph, t_paths **paths, size_t nb_ants)
{
	t_paths	*potential_paths;
	t_paths	*all_paths;
	t_graph	*history[100];

	reset_history(history);
	push_history(history, graph);
	potential_paths = NULL;
	find_potential_paths(graph, &potential_paths, history, paths);
	all_paths = potential_paths;

	select_optimal_paths(all_paths, paths, nb_ants);
}
