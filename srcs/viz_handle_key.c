/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_handle_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:25:35 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/11 10:25:37 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	place_ant(t_mlx_win *mlx_win, size_t i, t_paths *paths)
{
	char		*name;
	size_t		ant_nb;

	ant_nb = (paths->ants)[i].ant_nb;
	name = get_room_name(paths, (paths->ants)[i].room_nb);
	draw_ant(ant_nb, name, mlx_win, 0);
}

void	erase_ant(t_mlx_win *mlx_win, size_t i, t_paths *paths)
{
	char		*name;
	size_t		ant_nb;

	ant_nb = (paths->ants)[i].ant_nb;
	name = get_room_name(paths, (paths->ants)[i].room_nb);
	draw_ant(ant_nb, name, mlx_win, 1);
}

void	go_back(t_mlx_win *mlx_win, t_paths *paths)
{
	size_t		i;

	mlx_win->turn_nb--;
	while (paths)
	{
		i = 0;
		while (i < paths->nb_ants)
		{
			if ((paths->ants)[i].room_nb > 0 && \
				(paths->ants)[i].room_nb < (int)paths->path_size)
				erase_ant(mlx_win, i, paths);
			(paths->ants)[i].room_nb--;
			i++;
		}
		i = 0;
		while (i < paths->nb_ants)
		{
			if ((paths->ants)[i].room_nb >= 0 && \
				(paths->ants)[i].room_nb < (int)paths->path_size)
				place_ant(mlx_win, i, paths);
			i++;
		}
		paths = paths->next;
	}
}

void	go_fwd(t_mlx_win *mlx_win, t_paths *paths)
{
	size_t		i;

	mlx_win->turn_nb++;
	while (paths)
	{
		i = 0;
		while (i < paths->nb_ants)
		{
			if ((paths->ants)[i].room_nb >= 0 && \
				(paths->ants)[i].room_nb < (int)paths->path_size - 1)
				erase_ant(mlx_win, i, paths);
			(paths->ants)[i].room_nb++;
			i++;
		}
		i = 0;
		while (i < paths->nb_ants)
		{
			if ((paths->ants)[i].room_nb > 0 && \
				(paths->ants)[i].room_nb < (int)paths->path_size)
				place_ant(mlx_win, i, paths);
			i++;
		}
		paths = paths->next;
	}
}

int	handle_key(int key, void *param)
{
	t_mlx_win	*mlx_win;
	t_paths		*paths;

	mlx_win = (t_mlx_win *)param;
	paths = mlx_win->optimal_paths;
	if (key == 53)
		escape(mlx_win);
	if (key == 123 && mlx_win->turn_nb > 0)
		go_back(mlx_win, paths);
	if (key == 124 && mlx_win->turn_nb < mlx_win->max_turns)
		go_fwd(mlx_win, paths);
	return (0);
}
