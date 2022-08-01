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

static	void	get_paths(t_all_paths_combos *all_paths_combos, t_room *graph, t_data *data)
{
	int	i;
	int	j;
	t_room	*end;
	t_room	*node;
	t_paths *path_el;
	t_paths *paths;
	t_path_node *path_node;
	size_t	path_size;

	i = 0;
	paths = NULL;
	end = search_for(data->exit_room, data);
	while (i < end->nb_links)
	{
		if (end->links[i]->reverse)
		{
			path_el = create_path_el(); //
			
			path_size = 2;
			path_node = (t_path_node *)malloc(sizeof(t_path_node));
			if (!path_node)
				handle_error();
			path_node->next = NULL;
			path_node->node = end;
			path_el->path = path_node;
			j = 0;
			node = end->links[i];
			while (node && node != graph)
			{
				path_size++;
				path_node = (t_path_node *)malloc(sizeof(t_path_node));
				if (!path_node)
					handle_error();
				path_node->next = NULL;
				path_node->node = node;
				push_front(&(path_el->path), path_node);
				node = node->reverse;
			}
			if (node != graph)
				ft_putstr("ALERT so here we have a path that ends with a node other than start, this should NEVER happen\n");
			path_node = (t_path_node *)malloc(sizeof(t_path_node));
			if (!path_node)
				handle_error();
			path_node->next = NULL;
			path_node->node = graph;
			push_front(&(path_el->path), path_node);
			path_el->path_size = path_size;
			if (!paths)
				paths = path_el;
			else
				lst_add_in_order(&paths, path_el);
		}
		i++;
	}
	all_paths_combos->arr[all_paths_combos->counter] = paths;
	all_paths_combos->counter++;
}

void	calc_solution(t_paths **solution, t_all_paths_combos *all_paths_combos, size_t nb_ants)
{
	int	k;
	size_t	shortest_nb_turns;

	k = 1; // what if there is not even one path combination???
	distribute_ants(all_paths_combos->arr[0], nb_ants);
	shortest_nb_turns = all_paths_combos->arr[0]->path_size + all_paths_combos->arr[0]->nb_ants;
	*solution = all_paths_combos->arr[0];
	while (k < all_paths_combos->counter)
	{
		distribute_ants(all_paths_combos->arr[k], nb_ants);
		if (all_paths_combos->arr[k]->path_size + all_paths_combos->arr[k]->nb_ants < shortest_nb_turns)
		{
			shortest_nb_turns = all_paths_combos->arr[k]->path_size + all_paths_combos->arr[k]->nb_ants;
			*solution = all_paths_combos->arr[k];
		}
		k++;
	}
}

void	init_combos(t_all_paths_combos **all_paths_combos)
{
	// make it dynamic...?
	(*all_paths_combos) = (t_all_paths_combos *)malloc(sizeof(t_all_paths_combos)); // if null
	(*all_paths_combos)->size = 300;
	(*all_paths_combos)->counter = 0;
	(*all_paths_combos)->arr = (t_paths **)malloc(sizeof(t_paths *) * 300); // same
}

void	solve222(t_room *graph, t_data *data, char **start_and_end, size_t nb_ants)
{
	t_hist	*path;
	t_all_paths_combos	*all_paths_combos;
	int	i;
	t_paths *solution;

	init_combos(&all_paths_combos);
	while (1)
	{
		path = get_aug_path(graph, start_and_end);
		if (!path)
			break ;
		i = path->counter - 1;
		while (i > 0)
		{
			//if (path->arr[i - 1]->reverse && path->arr[i - 1]->reverse != path->arr[i])
				//ft_putstr("ALERT so here we are apparently crossing another path...?\n");
			if (path->arr[i - 1]->reverse == path->arr[i])
				path->arr[i - 1]->reverse = NULL;
			else
				path->arr[i]->reverse = path->arr[i - 1];
			i--;
		}
		get_paths(all_paths_combos, graph, data);
	}
	calc_solution(&solution, all_paths_combos, nb_ants);
	ft_putstr("\n");
	display_result(solution, nb_ants);
	if (data->show_paths)
	{
		ft_putstr("\n********************\n\nThese are the paths that make up the solution:\n\n");
		print_paths(solution);
		ft_putstr("********************\n\n");
		ft_putstr("The number of turns is ");
		ft_putnbr((int)(solution->path_size + solution->nb_ants - 2));
		ft_putstr("\n\n");
	}
	if (data->visualizer)
		visualizer(graph, nb_ants, solution, start_and_end);
}

void	solve(t_room *graph, t_data *data)
{
	char	*start_and_end[2];

	start_and_end[0] = graph->name;
	start_and_end[1] = data->exit_room;
	solve222(graph, data, start_and_end, data->ants);
}
