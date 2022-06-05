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

void	find_shortest_paths(t_graph *graph, t_paths **paths)
{
	t_paths	*potential_paths;
	t_paths	*t_paths_ptr;
	t_graph	*history[100];
	t_paths	*shortest;
	size_t	shortest_size;

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

		//copy_path(shortest, &shortest_copy);
		// instead of doing this, dont forget to free the other ones from potential paths ie up until shortest and after shortest
		shortest->next = NULL;

		// from all the potential paths, find the shortest one and add it to paths linked list
		if (!(*paths))
			*paths = shortest;
		else
			lst_add_back((t_void_list *)*paths, (t_void_list *)shortest);
	}
}
