/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:14:34 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/07 13:29:38 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	display_options(t_data *data, t_room *graph, \
	t_paths *solution, t_vector *all_paths_combos)
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
		visualizer(graph, data, solution, all_paths_combos);
}

void	solve(t_room *graph, t_data *data)
{
	size_t				nb_ants;
	char				*start_and_end[2];
	t_vector			*all_paths_combos;
	t_paths				*solution;

	nb_ants = data->ants;
	start_and_end[0] = data->start_room_name;
	start_and_end[1] = data->end_room_name;
	if (!init_vect(&all_paths_combos, 30))
		exit_solver(all_paths_combos, data);
	handle_start_to_end_path(graph, data, all_paths_combos);
	edmond_karp_with_a_twist(graph, data, start_and_end, all_paths_combos);
	handle_start_to_end_path2(graph, data, all_paths_combos);
	if (find_best_solution(&solution, all_paths_combos, nb_ants))
	{
		if (!data->no_map)
			write(1, data->map, data->index_line);
		display_result(solution, nb_ants, all_paths_combos, data);
		display_options(data, graph, solution, all_paths_combos);
	}
	else
		exit_solver(all_paths_combos, data);
	free_combos(all_paths_combos);
}
