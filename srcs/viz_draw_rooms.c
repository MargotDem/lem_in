/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_draw_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:58:51 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/05 20:58:55 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	draw_room(t_mlx_win *mlx_win, t_room *node)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	room_size;

	room_size = 10;
	if (strings_match(node->name, mlx_win->start) || \
		strings_match(node->name, mlx_win->end))
		room_size = 20;
	x = node->abscissa * 30 + 40;
	y = node->ordinate * 30 + 40;
	i = y - room_size;
	while (i < y + room_size)
	{
		j = x - room_size;
		while (j < x + room_size)
		{
			mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, j, i, \
				mlx_win->room_color);
			j++;
		}
		i++;
	}
}

void	draw_rooms(t_mlx_win *mlx_win, t_room *node, t_vector *history)
{
	int		total_links;
	t_room	**links;
	t_room	*link;
	int		i;
	int		coords[2];

	total_links = node->total_links;
	links = node->links;
	i = 0;
	if (not_in_history(node, history))
		push_to_vect(history, node);
	draw_room(mlx_win, node);
	coords[0] = node->abscissa * 30 + 40;
	coords[1] = node->ordinate * 30 + 40;
	while (i < total_links)
	{
		link = links[i];
		draw_line(mlx_win, coords, link->abscissa * 30 + 40, \
			link->ordinate * 30 + 40);
		if (not_in_history(link, history))
			draw_rooms(mlx_win, link, history);
		i++;
	}
}
