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

void	escape(t_mlx_win *mlx_win, t_data *data, t_vector *all_paths_combos)
{
	(void)data;
	(void)all_paths_combos;
	mlx_destroy_window(mlx_win->mlx_ptr, mlx_win->window);
	//exit(0);
	exit_solver(all_paths_combos, data);
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

void	visualizer(t_room *graph, t_data *data, \
	t_paths *optimal_paths, t_vector *all_paths_combos)
{
	t_mlx_win	*mlx_win;
	t_vector	*history;

	init_viz(graph, data, optimal_paths, &mlx_win);
	color_background(mlx_win);
	history = NULL;
	init_vect(&history, 20);
	draw_rooms(mlx_win, graph, history);
	initialize_ants_positions(optimal_paths, all_paths_combos, data);
	draw_ants_start(optimal_paths, mlx_win);
	mlx_key_hook(mlx_win->window, handle_key, (void *)mlx_win);
	mlx_loop(mlx_win->mlx_ptr);
}
