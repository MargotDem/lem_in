/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_draw_ant.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:49:20 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/11 09:49:21 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	draw_it(t_mlx_win *mlx_win, int ant_size, int color, int *x_y_erase)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	erase;

	x = x_y_erase[0];
	y = x_y_erase[1];
	erase = x_y_erase[2];
	i = y - ant_size;
	while (i < y + ant_size)
	{
		j = x - ant_size;
		while (j < x + ant_size)
		{
			if (erase)
				mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, j, i, \
					mlx_win->room_color);
			else
				mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, j, i, color);
			j++;
		}
		i++;
	}	
}

void	draw_ant(size_t ant_nb, char *name, t_mlx_win *mlx_win, int erase)
{
	int		x_y_erase[3];
	int		ant_size;
	t_room	*node_to_find;

	ant_size = 5;
	node_to_find = search_for(name, mlx_win->data);
	x_y_erase[0] = node_to_find->abscissa * 30 + 40;
	x_y_erase[1] = node_to_find->ordinate * 30 + 40;
	if (strings_match(name, mlx_win->start))
	{
		x_y_erase[0] = 100 + ant_nb * ant_size * 3 - 15;
		x_y_erase[1] = 60;
	}
	else if (strings_match(name, mlx_win->end))
	{
		x_y_erase[0] = 100 + ant_nb * ant_size * 3 - 15;
		x_y_erase[1] = mlx_win->window_length - 60;
	}
	x_y_erase[2] = erase;
	draw_it(mlx_win, ant_size, get_ant_color(ant_nb), x_y_erase);
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
