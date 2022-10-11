/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:06:28 by mde-maul          #+#    #+#             */
/*   Updated: 2022/08/05 09:01:52 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	escape(t_mlx_win *mlx_win)
{
	mlx_destroy_window(mlx_win->mlx_ptr, mlx_win->window);
	exit(0);
}

int	get_ant_color(size_t ant_nb)
{
	int	color;
	int	red;
	int	green;
	int	blue;

	if (ant_nb < 6)
		ant_nb = ant_nb * 10;
	red = (ant_nb * ant_nb * 3) % 255;
	green = (ant_nb * 4 * ant_nb) % 255;
	blue = (ant_nb * 24) % 255;
	if (red < 125)
		red += 80;
	color = 0x000000 | red << 16 | green << 8 | blue;
	return (color);
}

void	draw_ant(size_t ant_nb, char *name, t_mlx_win *mlx_win, int erase)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	ant_size;
	int	color;
	t_room	*node_to_find = NULL;

	color = get_ant_color(ant_nb);
	ant_size = 3;
	node_to_find = search_for(name, mlx_win->data);
	if (node_to_find)
	{
		x = node_to_find->abscissa * 30 + 40;
		y = node_to_find->ordinate * 30 + 40;
		if (strings_match(name, mlx_win->start))
		{
			x = 100 + ant_nb * ant_size * 3 - 15;
			y = 60;
		}
		else if (strings_match(name, mlx_win->end))
		{
			x = 100 + ant_nb * ant_size * 3 - 15;
			y = mlx_win->window_length - 60;
		}
		i = y - ant_size;
		while (i < y + ant_size)
		{
			j = x - ant_size;
			while (j < x + ant_size)
			{
				if (erase)
					mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, j, i, mlx_win->room_color);
				else
					mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, j, i, color);
				j++;
			}
			i++;
		}
	}
	else
		ft_putstr("not found\n");
}

int	handle_key(int key, void *param)
{
	t_mlx_win	*mlx_win;
	t_paths		*paths_ptr;
	size_t		i;
	char		*name;
	size_t		ant_nb;

	mlx_win = (t_mlx_win *)param;
	paths_ptr = mlx_win->optimal_paths;
	if (key == 53)
		escape(mlx_win);
	if (key == 123 && mlx_win->turn_nb > 0)
	{
		mlx_win->turn_nb--;
		while (paths_ptr)
		{
			i = 0;
			while (i < paths_ptr->nb_ants)
			{
				(paths_ptr->ants)[i].room_nb--;
				if ((paths_ptr->ants)[i].room_nb >= 0 && (paths_ptr->ants)[i].room_nb < (int)paths_ptr->path_size - 1)
				{
					ant_nb = (paths_ptr->ants)[i].ant_nb;
					name = get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb + 1);
					draw_ant(ant_nb, name, mlx_win, 1);
				}
				i++;
			}
			i = 0;
			while (i < paths_ptr->nb_ants)
			{
				if ((paths_ptr->ants)[i].room_nb >= 0 && (paths_ptr->ants)[i].room_nb < (int)paths_ptr->path_size)
				{
					ant_nb = (paths_ptr->ants)[i].ant_nb;
					name = get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb);
					draw_ant(ant_nb, name, mlx_win, 0);
				}
				i++;
			}
			paths_ptr = paths_ptr->next;
		}
	}
	if (key == 124 && mlx_win->turn_nb < mlx_win->max_turns)
	{
		mlx_win->turn_nb++;
		while (paths_ptr)
		{
			i = 0;
			while (i < paths_ptr->nb_ants)
			{
				(paths_ptr->ants)[i].room_nb++;
				if ((paths_ptr->ants)[i].room_nb > 0 && (paths_ptr->ants)[i].room_nb < (int)paths_ptr->path_size)
				{
					ant_nb = (paths_ptr->ants)[i].ant_nb;
					name = get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb - 1);
					draw_ant(ant_nb, name, mlx_win, 1);
				}
				i++;
			}
			i = 0;
			while (i < paths_ptr->nb_ants)
			{
				if ((paths_ptr->ants)[i].room_nb > 0 && (paths_ptr->ants)[i].room_nb < (int)paths_ptr->path_size)
				{
					ant_nb = (paths_ptr->ants)[i].ant_nb;
					name = get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb);
					draw_ant(ant_nb, name, mlx_win, 0);
				}
				i++;
			}
			paths_ptr = paths_ptr->next;
		}
	}
	return (0);
}

void	color_background(t_mlx_win *mlx_win)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < mlx_win->window_length)
	{
		j = 0;
		while (j < mlx_win->window_width)
		{
			mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, (int)j, \
				(int)i, mlx_win->background_color);
			j++;
		}
		i++;
	}
}

void	draw_ants_start(t_paths *paths_ptr, t_mlx_win *mlx_win)
{
	size_t	i;
	size_t	ant_nb;
	char	*name;

	while (paths_ptr)
	{
		i = 0;
		while (i < paths_ptr->nb_ants)
		{
			ant_nb = (paths_ptr->ants)[i].ant_nb;
			name = get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb);
			draw_ant(ant_nb, name, mlx_win, 0);
			i++;
		}
		paths_ptr = paths_ptr->next;
	}
}

void	visualizer(t_room *graph, t_data *data, t_paths *optimal_paths)
{
	t_mlx_win	*mlx_win;
	t_vector	*history;

	init_viz(graph, data, optimal_paths, &mlx_win);
	color_background(mlx_win);
	history = NULL;
	init_vect(&history, 20);
	draw_rooms(mlx_win, graph, history);
	initialize_ants_positions(optimal_paths);
	draw_ants_start(optimal_paths, mlx_win);
	mlx_key_hook(mlx_win->window, handle_key, (void *)mlx_win);
	mlx_loop(mlx_win->mlx_ptr);
}
