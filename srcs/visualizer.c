/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:06:28 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/11 16:06:29 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	draw_room(t_mlx_win *mlx_win, t_room *node, size_t scale, size_t margin)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	color;
	int	room_size;

	room_size = 10;
	if (strings_match(node->name, mlx_win->start_and_end[0]) || strings_match(node->name, mlx_win->start_and_end[1]))
		room_size = 20;
	x = node->x * scale + margin;
	y = node->y * scale + margin;
	color = mlx_win->room_color;
	i = y - room_size;
	while (i < y + room_size)
	{
		j = x - room_size;
		while (j < x + room_size)
		{
			mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, j, i, color);
			j++;
		}
		i++;
	}
}

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
	int	tmp_x;
	int	tmp_y;
	int	color;

	color = mlx_win->room_color;
	if (y_b <= y_a)
	{
		tmp_x = x_a;
		tmp_y = y_a;
		x_a = x_b;
		y_a = y_b;
		x_b = tmp_x;
		y_b = tmp_y;
	}
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

void	draw_line(t_mlx_win *mlx_win, int x_a, int y_a, int x_b, int y_b)
{
	int	x;
	int	y;
	int	color;

	x = x_a;
	y = y_a;
	color = mlx_win->room_color;
	if (x_b - x_a >= abs(y_b - y_a))
	{
		while (x < x_b)
		{
			y = round_point(((float)(y_b - y_a) / \
				(float)(x_b - x_a)) * (x - x_a) + \
				y_a + 0.5);
			mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, x, y, color);
			x++;
		}
	}
	else
		draw_steep_line(mlx_win, x_a, y_a, x_b, y_b);
}

void	draw_rooms(t_mlx_win *mlx_win, t_room *node, t_hist *history)
{
	size_t	nb_links;
	t_room	**links;
	t_room	*link;
	size_t i;
	size_t	scale;
	size_t	margin;

	scale = mlx_win->scale;
	margin = mlx_win->margin;
	nb_links = node->nb_links;
	links = node->links;
	i = 0;
	if (not_in_history(node, history))
		push_history(history, node);
	draw_room(mlx_win, node, scale, margin);
	while (i < nb_links)
	{
		link = links[i];
		draw_line(mlx_win, node->x * scale + margin, node->y * scale + margin, link->x * scale + margin, link->y * scale + margin);
		if (not_in_history(link, history))
			draw_rooms(mlx_win, link, history);
		i++;
	}
}

void	escape(t_mlx_win *mlx_win)
{
	mlx_destroy_window(mlx_win->mlx_ptr, mlx_win->window);
	exit(0);
}

void	draw_ant(size_t ant_nb, char *name, t_mlx_win *mlx_win, int erase)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	ant_size;
	size_t	scale;
	size_t	margin;
	int	color;
	t_hist	*history;
	t_room *node_to_find = NULL;

	scale = mlx_win->scale;
	margin = mlx_win->margin;
	if (ant_nb == 1)
		color = 0x02ebd7;
	else if (ant_nb == 2)
		color = 0xeb02c4;
	else if (ant_nb == 3)
		color = 0x28e053;
	else if (ant_nb == 4)
		color = 0xe1e81a;
	else if (ant_nb == 5)
		color = 0xffa200;
	else if (ant_nb == 6)
		color = 0xff1e00;
	else
		color = 0x0244eb;
	ant_size = 3;
	history = NULL;
	init_history(&history, 4);
	find_node(mlx_win->graph, history, name, &node_to_find);
	if (node_to_find)
	{
		x = node_to_find->x * scale + margin;
		y = node_to_find->y * scale + margin;
		if (strings_match(name, mlx_win->start_and_end[0]) || strings_match(name, mlx_win->start_and_end[1]))
			x += ant_nb * ant_size * 3 - 15;
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
		printf("not found\n");
}

int	handle_key(int key, void *param)
{
	t_mlx_win	*mlx_win;
	t_paths	*paths_ptr;
	size_t	i;
	char	*name;
	size_t	ant_nb;

	mlx_win = (t_mlx_win *)param;
	//printf("key is %d\n", key);
	paths_ptr = mlx_win->optimal_paths;
	if (key == 53)
		escape(mlx_win);
	if (key == 123 && mlx_win->turn_nb > 0)
	{
		mlx_win->turn_nb--;
		printf("turn %zu: ", mlx_win->turn_nb);
		while (paths_ptr)
		{
			i = 0;
			while (i < paths_ptr->nb_ants)
			{
				(paths_ptr->ants)[i].room_nb--;
				if ((paths_ptr->ants)[i].room_nb >= 0 && (paths_ptr->ants)[i].room_nb < (int)paths_ptr->path_size - 1)
				{
					ant_nb = (paths_ptr->ants)[i].ant_nb;
					printf("annt nb is %zu, room name is %s\n", ant_nb, get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb + 1));
					draw_ant(ant_nb, get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb + 1), mlx_win, 1);
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
					//printf("L%zu-%s ", (paths_ptr->ants)[i].ant_nb, get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb));
				}
				i++;
			}
			paths_ptr = paths_ptr->next;
		}
		printf("\n");
	}
	if (key == 124 && mlx_win->turn_nb < mlx_win->max_turns)
	{
		mlx_win->turn_nb++;
		printf("turn %zu: ", mlx_win->turn_nb);
		while (paths_ptr)
		{
			i = 0;
			while (i < paths_ptr->nb_ants)
			{
				(paths_ptr->ants)[i].room_nb++;
				if ((paths_ptr->ants)[i].room_nb > 0 && (paths_ptr->ants)[i].room_nb < (int)paths_ptr->path_size)
				{
					ant_nb = (paths_ptr->ants)[i].ant_nb;
					draw_ant(ant_nb, get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb - 1), mlx_win, 1);
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
					//printf("L%zu-%s ", (paths_ptr->ants)[i].ant_nb, get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb));
				}
				i++;
			}
			paths_ptr = paths_ptr->next;
		}
		printf("\n");
	}
	(void)i;
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
			mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, (int)j, (int)i, 0xededed);
			j++;
		}
		i++;
	}
}

static void	initialize_ants_positions(t_paths *paths)
{
	t_paths	*paths_ptr;
	size_t	i;

	paths_ptr = paths;
	while (paths_ptr)
	{
		i = 0;
		while (i < paths_ptr->nb_ants)
		{
			(paths_ptr->ants)[i].room_nb = -i;
			i++;
		}
		paths_ptr = paths_ptr->next;
	}
}

void	visualizer(t_room *graph, size_t nb_ants, t_paths *optimal_paths, char **start_and_end)
{
	t_mlx_win	*mlx_win;
	t_hist	*history;
	(void)nb_ants;
	(void)optimal_paths;

	mlx_win = (t_mlx_win *)malloc(sizeof(t_mlx_win));
	if (!mlx_win)
		handle_error();
	mlx_win->mlx_ptr = handle_null(mlx_init());
	mlx_win->window_width = 1500;
	mlx_win->window_length = 1100;
	mlx_win->window = handle_null(mlx_new_window(mlx_win->mlx_ptr, mlx_win->window_width, \
		mlx_win->window_length, "Lem in"));
	mlx_win->graph = graph;
	mlx_win->nb_ants = nb_ants;
	mlx_win->optimal_paths = optimal_paths;
	mlx_win->turn_nb = 0;
	mlx_win->max_turns = optimal_paths->nb_ants + optimal_paths->path_size - 2;
	mlx_win->scale = 30;
	mlx_win->margin = 40;
	mlx_win->room_color = 0xd1c4ff;
	mlx_win->start_and_end = start_and_end;
	printf("nb of turns is %zu\n", mlx_win->max_turns);
	color_background(mlx_win);
	history = NULL;
	init_history(&history, 4);
	draw_rooms(mlx_win, graph, history);
	initialize_ants_positions(optimal_paths);

	t_paths	*paths_ptr;
	paths_ptr = optimal_paths;
	size_t i;
	char	*name;
	size_t	ant_nb;
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

	mlx_key_hook(mlx_win->window, handle_key, (void *)mlx_win);
	mlx_loop(mlx_win->mlx_ptr);
	(void)i;
}
