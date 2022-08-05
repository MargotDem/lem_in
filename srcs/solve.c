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
	(*all_paths_combos) = (t_all_paths_combos *)handle_null(\
		malloc(sizeof(t_all_paths_combos)));
	printf("(*all_paths_combos): %p\n", (*all_paths_combos));
	(*all_paths_combos)->size = size;
	(*all_paths_combos)->counter = 0;
	(*all_paths_combos)->arr = (t_paths **)handle_null(\
		malloc(sizeof(t_paths *) * size));
	printf("(*all_paths_combos)->arr: %p\n", (*all_paths_combos)->arr);
	ft_memset((void *)((*all_paths_combos)->arr), 0, size);
}

void	free_to_be_visited(t_hist **to_be_visited)
{
	int	j;
	int	counter;

	j = 0;
	counter = (*to_be_visited)->counter;
	while (j < counter)
	{
		if ((*to_be_visited)->arr[j]->history)
			free_history(&(*to_be_visited)->arr[j]->history);
		j++;
	}
	free_history(to_be_visited);
}

void	edmond_karp_with_a_twist(t_room *graph, t_data *data, \
	char **start_and_end, t_all_paths_combos	*all_paths_combos)
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

void	display_options(t_data *data, t_room *graph, t_paths *solution, char **start_and_end)
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

void	free_path(t_path_node *path)
{
	t_path_node	*next;

	while (path)
	{
		next = path->next;
		free(path);
		path = next;
	}
}

void	free_path_el(t_paths *paths)
{
	t_paths	*next;

	while (paths)
	{
		next = paths->next;
		free_path(paths->path);
		if (paths->ants)
			free(paths->ants);
		paths = next;
	}
}

void	free_combos(t_all_paths_combos *all_paths_combos)
{
	int	counter;
	int	j;

	counter = all_paths_combos->counter;
	j = 0;
	while (j < counter)
	{
		free_path_el(all_paths_combos->arr[j]);
		j++;
	}
	free(all_paths_combos->arr);
	free(all_paths_combos);
}

void	solve(t_room *graph, t_data *data)
{
	size_t				nb_ants;
	char				*start_and_end[2];
	t_all_paths_combos	*all_paths_combos;
	t_paths				*solution;

	nb_ants = data->ants;
	start_and_end[0] = graph->name;
	start_and_end[1] = data->end_room_name;
	init_combos(&all_paths_combos);
	edmond_karp_with_a_twist(graph, data, start_and_end, all_paths_combos);
	calc_solution(&solution, all_paths_combos, nb_ants);
	display_result(solution, nb_ants);
	display_options(data, graph, solution, start_and_end);
	free_combos(all_paths_combos);
}
