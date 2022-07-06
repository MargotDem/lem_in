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

void solve(t_room *start, t_data *data)
{
	size_t	nb_ants;
	t_hist	*history;
	t_paths	*optimal_paths;
	char	*start_and_end[2];

	nb_ants = data->ants;
	printf("***** the tree ***** \n");
	history = NULL;
	init_history(&history, 4);
	print_graph(start, history);
	print_history(history);
	printf("******\n\n\n");

	optimal_paths = NULL;
	start_and_end[0] = start->name;
	start_and_end[1] = data->exit_room;
	find_optimal_paths(start, &optimal_paths, nb_ants, start_and_end);
	distribute_ants(optimal_paths, nb_ants);
	printf("\n\nTHE PATHS ARE:\n\n");
	print_paths(optimal_paths);
	display_result(optimal_paths, nb_ants);
	visualizer(start, nb_ants, optimal_paths, start_and_end);
	printf("\n\n\n\n");
}
