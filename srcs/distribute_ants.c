/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:23:58 by mde-maul          #+#    #+#             */
/*   Updated: 2022/08/01 18:23:59 by mde-maul         ###   ########.fr       */
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
