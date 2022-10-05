/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_solution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:46:40 by mde-maul          #+#    #+#             */
/*   Updated: 2022/09/22 15:46:42 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	switch_ant(t_paths *path, t_paths *next, int *move)
{
	*move = 1;
	(path->nb_ants)--;
	(next->nb_ants)++;
}

void	distribute_ants(t_paths *paths, size_t nb_ants)
{
	t_paths	*next;
	t_paths	*paths_ptr;
	int		move;

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
		while (get_nb_turns(paths_ptr) - 1 >= get_nb_turns(next) + 1)
			switch_ant(paths_ptr, next, &move);
		if (paths_ptr != paths && next->nb_ants && \
				get_nb_turns(next) == get_nb_turns(paths_ptr) - 1)
			switch_ant(paths_ptr, next, &move);
		paths_ptr = next;
		if (!paths_ptr->next && move)
			paths_ptr = paths;
	}
}

int	find_best_solution(t_paths **solution, \
	t_vector *all_paths_combos_struct, size_t nb_ants)
{
	int		k;
	size_t	shortest_nb_turns;
	size_t	new_nb_turns;
	t_paths	**all_paths_combos;

	all_paths_combos = (t_paths **)(all_paths_combos_struct->arr);
	if (!all_paths_combos[0])
		return (0);
	distribute_ants(all_paths_combos[0], nb_ants);
	shortest_nb_turns = get_nb_turns(all_paths_combos[0]);
	*solution = all_paths_combos[0];
	k = 1;
	while (k < (int)all_paths_combos_struct->counter)
	{
		distribute_ants(all_paths_combos[k], nb_ants);
		new_nb_turns = get_nb_turns(all_paths_combos[k]);
		if (new_nb_turns < shortest_nb_turns)
		{
			shortest_nb_turns = new_nb_turns;
			*solution = all_paths_combos[k];
		}
		k++;
	}
	return (1);
}
