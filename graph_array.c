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

	if (!paths)
		return ;
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
	t_paths	*optimal_paths;

	optimal_paths = NULL;
	find_optimal_paths(graph, &optimal_paths, nb_ants);
	distribute_ants(optimal_paths, nb_ants);
	printf("\n\nTHE PATHS ARE:\n\n");
	print_paths(optimal_paths);
	display_result(optimal_paths, nb_ants);
	visualizer(graph, nb_ants, optimal_paths);
}

void graph_array(void)
{
	t_graph	*graph;
	size_t	nb_ants;
	t_graph	*history[100];

	make_graph6(&graph);
	printf("***** the tree ***** \n");
	reset_history(history);
	print_graph(graph, history);
	printf("******\n\n\n");

	nb_ants = 14;
	
	solve(graph, nb_ants);
}

/*
*/
