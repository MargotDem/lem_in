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

void	distribute_ants3(t_paths *paths, size_t nb_ants)
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


void	distribute_ants2(t_paths *paths, size_t nb_ants)
{
	t_paths	*next;
	t_paths	*paths_ptr;
	int	move;

	if (!paths)
		return ;
	set_paths_size(paths);
	//printf("size of the first path is %zu\n", paths->path_size);
	paths->nb_ants = nb_ants;
	paths_ptr = paths;
	while (1)
	{
		move = 0;
		if (!paths_ptr->next)
			paths_ptr = paths;
		if (!paths_ptr->next) // if this is still the case it means there's only one path
			break ;
		next = paths_ptr->next;
		/*if (next->path_size == 18)
		{
			printf("YES VIIFHWEFWBEIUBF\n");
			if (paths_ptr->nb_ants + paths_ptr->path_size - 1 < next->nb_ants + next->path_size + 1)
				printf("YES VIIvewvewvwevwevwefewFHWEFWBEIUBF\n");
		}*/
		if (paths_ptr->nb_ants + paths_ptr->path_size - 1 < next->nb_ants + next->path_size + 1)
		{
				//printf("LETS BREEAAKKKK, the first path starts with %s and second starts with %s,\nthe first has %zu ants and second has %zu\n", paths_ptr->path->next->node->name, next->path->next->node->name, paths_ptr->nb_ants, next->nb_ants);

			//break ;
			if (next->nb_ants != 0)
			{
				//paths_ptr = paths;
				//continue ;
				//break ;
				printf("LETS BREEAAKKKK, the first path starts with %s and second starts with %s,\nthe first has %zu ants and second has %zu\n", paths_ptr->path->next->node->name, next->path->next->node->name, paths_ptr->nb_ants, next->nb_ants);
				//break ;
			}
			else
			{
			}
		}
		// not sure if needed now that shortest path fixed
		//while (paths_ptr->nb_ants > 0 && paths_ptr->nb_ants + paths_ptr->path_size - 1 >= next->nb_ants + next->path_size + 1)
		while (paths_ptr->nb_ants + paths_ptr->path_size - 1 >= next->nb_ants + next->path_size + 1)
		{
			move = 1;
			(paths_ptr->nb_ants)--;
			(next->nb_ants)++;
			//paths_ptr = paths;
			//continue ;
		}
		printf("ok so here, the first path starts with %s and second starts with %s,\nthe first has %zu ants and second has %zu\n", paths_ptr->path->next->node->name, next->path->next->node->name, paths_ptr->nb_ants, next->nb_ants);
		paths_ptr = next;
		printf("\n\n");
		if (next->nb_ants == 0)
			break;
		//if (next->nb_ants == 0 && !move)
			//break ;
	}
}

void	distribute_ants(t_paths *paths, size_t nb_ants)
{
	t_paths	*next;
	t_paths	*paths_ptr;
	int	move;

	if (!paths)
		return ;
	set_paths_size(paths);
	paths->nb_ants = nb_ants;
	paths_ptr = paths;
	while (paths_ptr->next)
	{
		if (paths_ptr == paths)
			move = 0;
		next = paths_ptr->next;
		while (paths_ptr->nb_ants + paths_ptr->path_size - 1 >= next->nb_ants + next->path_size + 1)
		{
			move = 1;
			(paths_ptr->nb_ants)--;
			(next->nb_ants)++;
			//paths_ptr = paths;
			//continue ;
		}
		paths_ptr = next;
		if (!paths_ptr->next && move)
			paths_ptr = paths;

	}
}

void solve(t_room *start, t_data *data)
{
	size_t	nb_ants;
	t_hist	*history;
	t_paths	*optimal_paths;
	char	*start_and_end[2];

	nb_ants = data->ants;
	//printf("***** the tree ***** \n");
	history = NULL;
	init_history(&history, 2000);
	//print_graph(start, history);
	//printf("**************\n\n\n");
	printf("HERE before finding optimal paths\n");
	optimal_paths = NULL;
	start_and_end[0] = start->name;
	start_and_end[1] = data->exit_room;
	find_optimal_paths(start, &optimal_paths, nb_ants, start_and_end);
	//printf("\n\nand optimal path the first path nb ants is %zu\n", (optimal_paths)->nb_ants);
	distribute_ants(optimal_paths, nb_ants);
	//printf("and AFTER DISTRIB optimal path the first path nb ants is %zu\n", (optimal_paths)->nb_ants);
	printf("\n\nTHE OPTIMAL PATHS ARE:\n\n");
	print_paths(optimal_paths);
	printf("\n\nEND OF OPTIMAL PATHS:\n\n");
	display_result(optimal_paths, nb_ants);
	printf("nb of turns is %zu\n", optimal_paths->nb_ants + optimal_paths->path_size - 2);
	//visualizer(start, nb_ants, optimal_paths, start_and_end);
	printf("\n\n\n\n");
}
