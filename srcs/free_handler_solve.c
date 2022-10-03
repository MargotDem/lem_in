/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler_solve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:20:13 by mde-maul          #+#    #+#             */
/*   Updated: 2022/09/22 15:20:15 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		free(paths);
		paths = next;
	}
}

void	free_combos(t_vector *all_paths_combos)
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

void	free_history(t_hist **hist)
{
	if (*hist)
	{
		free((*hist)->arr);
		free(*hist);
		*hist = NULL;
	}
}
