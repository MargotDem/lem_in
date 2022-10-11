/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:10:46 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/11 09:10:48 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_reverse_edges(t_vector *path)
{
	int	i;

	i = path->counter - 1;
	while (i > 0)
	{
		if (((t_room *)(path->arr[i - 1]))->reverse == path->arr[i])
			((t_room *)(path->arr[i - 1]))->reverse = NULL;
		else
			((t_room *)(path->arr[i]))->reverse = path->arr[i - 1];
		i--;
	}
}

void	edmond_karp_with_a_twist(t_room *graph, t_data *data, \
	t_vector *all_paths_combos)
{
	t_vector	*path;
	t_vector	*to_be_visited;
	int			ret;

	while (1)
	{
		ret = get_aug_path(graph, data, &to_be_visited, &path);
		if (ret < 1)
		{
			if (!ret)
				exit_solver(all_paths_combos, data);
			free_to_be_visited(&to_be_visited);
			break ;
		}
		set_reverse_edges(path);
		get_paths(all_paths_combos, graph, data);
		free_to_be_visited(&to_be_visited);
	}
}
