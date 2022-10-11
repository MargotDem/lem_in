/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:11:51 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/07 11:34:20 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_viz(t_room *graph, t_data *data, t_paths *optimal_paths, \
	t_mlx_win **ptr)
{
	t_mlx_win	*mlx_win;

	mlx_win = (t_mlx_win *)handle_null(malloc(sizeof(t_mlx_win)));
	mlx_win->start = data->start_room_name;
	mlx_win->end = data->end_room_name;
	mlx_win->mlx_ptr = handle_null(mlx_init());
	mlx_win->data = data;
	mlx_win->window_width = 1800;
	mlx_win->window_length = 1200;
	mlx_win->window = handle_null(mlx_new_window(mlx_win->mlx_ptr, \
		mlx_win->window_width, mlx_win->window_length, "Lem in"));
	mlx_win->graph = graph;
	mlx_win->nb_ants = data->ants;
	mlx_win->optimal_paths = optimal_paths;
	mlx_win->turn_nb = 0;
	mlx_win->max_turns = optimal_paths->nb_ants + optimal_paths->path_size - 2;
	mlx_win->scale = 30;
	mlx_win->margin = 40;
	mlx_win->room_color = 0xd1c4ff;
	mlx_win->background_color = 0x012c73;
	*ptr = mlx_win;
}
