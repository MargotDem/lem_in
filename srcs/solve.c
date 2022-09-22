/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:14:34 by mde-maul          #+#    #+#             */
/*   Updated: 2022/08/05 09:01:01 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TODO make it dynamic...?
void	init_combos(t_all_paths_combos **all_paths_combos)
{
	size_t	size;

	size = 300;
	*all_paths_combos = (t_all_paths_combos *)handle_null(\
		malloc(sizeof(t_all_paths_combos)));
	(*all_paths_combos)->size = size;
	(*all_paths_combos)->counter = 0;
	(*all_paths_combos)->arr = (t_paths **)handle_null(\
		malloc(sizeof(t_paths *) * size));
	ft_bzero((void *)((*all_paths_combos)->arr), size);
}

void	edmond_karp_with_a_twist(t_room *graph, t_data *data, \
	char **start_and_end, t_all_paths_combos *all_paths_combos)
{
	t_hist	*path;
	t_hist	*to_be_visited;
	int		i;

	while (1)
	{
		path = get_aug_path(graph, start_and_end, &to_be_visited);
		if (!path)
		{
			free_to_be_visited(&to_be_visited);
			break ;
		}
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
		free_to_be_visited(&to_be_visited);
	}
}

void	display_options(t_data *data, t_room *graph, \
	t_paths *solution, char **start_and_end)
{
	if (data->print_paths)
	{
		ft_putstr("\n********************\n\n");
		ft_putstr("These are the paths that make up the solution:\n\n");
		print_paths(solution);
		ft_putstr("********************\n\nThe number of turns is ");
		ft_putnbr((int)(get_nb_turns(solution)));
		ft_putstr("\n\n");
	}
	if (data->visual)
		visualizer(graph, data, solution, start_and_end);
}

void	solve(t_room *graph, t_data *data)
{
	size_t				nb_ants;
	char				*start_and_end[2];
	t_all_paths_combos	*all_paths_combos;
	t_paths				*solution;

	nb_ants = data->ants;
	start_and_end[0] = data->start_room_name;
	start_and_end[1] = data->end_room_name;
	init_combos(&all_paths_combos);
	edmond_karp_with_a_twist(graph, data, start_and_end, all_paths_combos);
	find_best_solution(&solution, all_paths_combos, nb_ants);
	display_result(solution, nb_ants);
	display_options(data, graph, solution, start_and_end);
	free_combos(all_paths_combos);
}
