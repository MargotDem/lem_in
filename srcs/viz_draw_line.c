/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:31:22 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/05 20:31:25 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	round_point(float x)
{
	if ((int)(x * 10) % 10 >= 5)
		return ((int)x + 1);
	return ((int)x);
}

void	draw_steep_line(t_mlx_win *mlx_win, int x_a, int y_a, int x_b, int y_b)
{
	int	x;
	int	y;
	int	color;

	color = mlx_win->room_color;
	x = x_a;
	y = y_a;
	while (y < y_b)
	{
		x = round_point(x_a + (y - 0.5 - y_a) * \
			((float)(x_b - x_a) / \
			(float)(y_b - y_a)));
		mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, x, y, color);
		y++;
	}
}

//void	draw_line(t_mlx_win *mlx_win, int x_a, int y_a, int x_b, int y_b)
void	draw_line(t_mlx_win *mlx_win, int *coords_a, int x_b, int y_b)
{
	int	x;
	int	y;
	int	color;

	x = coords_a[0];
	y = coords_a[1];
	color = mlx_win->room_color;
	if (x_b - coords_a[0] >= abs(y_b - coords_a[1]))
	{
		while (x < x_b)
		{
			y = round_point(((float)(y_b - coords_a[1]) / \
				(float)(x_b - coords_a[0])) * (x - coords_a[0]) + \
				coords_a[1] + 0.5);
			mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, x, y, color);
			x++;
		}
	}
	else
		draw_steep_line(mlx_win, coords_a[0], coords_a[1], x_b, y_b);
}
