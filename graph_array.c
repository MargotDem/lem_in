/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:19:17 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/04 17:19:19 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	distribute_ants(t_paths *paths, size_t nb_ants)
{
	t_paths	*next;
	t_paths	*paths_ptr;

	set_paths_size(paths);
	paths->nb_ants = nb_ants;
	paths_ptr = paths;
	while (1)
	{
		if (!paths_ptr->next)
			paths_ptr = paths;
		if (!paths_ptr->next) // if this is still the case it means there's only one path
			break ;
		next = paths_ptr->next;
		if (paths_ptr->nb_ants + paths_ptr->path_size - 1 < next->nb_ants + next->path_size + 1)
			break ;
		while (paths_ptr->nb_ants + paths_ptr->path_size - 1 >= next->nb_ants + next->path_size + 1)
		{
			(paths_ptr->nb_ants)--;
			(next->nb_ants)++;
		}
		paths_ptr = next;
	}
}

void	solve(t_graph *graph, size_t nb_ants)
{
	t_paths	*paths;

	// find all possible disctinct paths from shortest to longest
	paths = NULL;
	find_optimal_paths(graph, &paths, nb_ants);
	printf("\n\nSMALLEST PATHS ARE:\n\n");
	
	// decide how many ants will take each path
	distribute_ants(paths, nb_ants);
	print_paths(paths);

	display_result(paths, nb_ants);
}

void graph_array(void)
{
	t_graph	*graph;
	size_t	nb_ants;
	t_graph	*history[100];
	
	make_graph5(&graph);
	printf("***** the tree ***** \n");
	reset_history(history);
	print_graph(graph, history);
	printf("******\n\n\n");

	/*
	t_graph *node_to_find = NULL;
	find_node(graph, history, "I", &node_to_find);
	reset_history(history);
	if (node_to_find)
		printf("thats the nodeee '%s'\n", node_to_find->name);
	else
		printf("not found\n");
	*/

	nb_ants = 20;
	solve(graph, nb_ants);
}
