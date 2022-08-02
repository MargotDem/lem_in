/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:14:34 by mde-maul          #+#    #+#             */
/*   Updated: 2022/07/25 21:14:36 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	calc_solution(t_paths **solution, \
	t_all_paths_combos *all_paths_combos, size_t nb_ants)
{
	int		k;
	size_t	shortest_nb_turns;
	size_t	new_nb_turns;

	if (!all_paths_combos->arr[0])
		handle_error();
	k = 1;
	distribute_ants(all_paths_combos->arr[0], nb_ants);
	shortest_nb_turns = get_nb_turns(all_paths_combos->arr[0]);
	*solution = all_paths_combos->arr[0];
	while (k < all_paths_combos->counter)
	{
		distribute_ants(all_paths_combos->arr[k], nb_ants);
		new_nb_turns = get_nb_turns(all_paths_combos->arr[k]);
		if (new_nb_turns < shortest_nb_turns)
		{
			shortest_nb_turns = new_nb_turns;
			*solution = all_paths_combos->arr[k];
		}
		k++;
	}
}

// TODO make it dynamic...?
void	init_combos(t_all_paths_combos **all_paths_combos)
{
	size_t	size;

	size = 300;
	(*all_paths_combos) = (t_all_paths_combos *)handle_null((void \
		*)malloc(sizeof(t_all_paths_combos)));
	(*all_paths_combos)->size = size;
	(*all_paths_combos)->counter = 0;
	(*all_paths_combos)->arr = (t_paths **)handle_null((void \
		*)malloc(sizeof(t_paths *) * size));
	ft_memset((void *)((*all_paths_combos)->arr), 0, size);
}

void	edmond_karp_with_a_twist(t_room *graph, t_data *data, \
	char **start_and_end, t_all_paths_combos	*all_paths_combos)
{
	t_hist	*path;
	int		i;

	while (1)
	{
		path = get_aug_path(graph, start_and_end);
		if (!path)
			break ;
		i = path->counter - 1;
		while (i > 0)
		{
			if (path->arr[i - 1]->reverse == path->arr[i])
				path->arr[i - 1]->reverse = NULL;
			else
				path->arr[i]->reverse = path->arr[i - 1];
			i--;
		}
		get_paths(all_paths_combos, graph, data);
	}
}

void	solve(t_room *graph, t_data *data)
{
	size_t				nb_ants;
	char				*start_and_end[2];
	t_all_paths_combos	*all_paths_combos;
	t_paths				*solution;

	nb_ants = data->ants;
	start_and_end[0] = graph->name;
	start_and_end[1] = data->exit_room;
	init_combos(&all_paths_combos);
	edmond_karp_with_a_twist(graph, data, start_and_end, all_paths_combos);
	calc_solution(&solution, all_paths_combos, nb_ants);
	display_result(solution, nb_ants);
	if (data->show_paths)
	{
		ft_putstr("\n********************\n\n");
		ft_putstr("These are the paths that make up the solution:\n\n");
		print_paths(solution);
		ft_putstr("********************\n\nThe number of turns is ");
		ft_putnbr((int)(get_nb_turns(solution)));
		ft_putstr("\n\n");
	}
	if (data->visualizer)
		visualizer(graph, nb_ants, solution, start_and_end);
}
