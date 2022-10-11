/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:37:29 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/07 11:16:40 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
// # include "mlx.h"
# include "parsing.h"

typedef struct s_path_node
{
	struct s_path_node	*next;
	t_room				*node;
}				t_path_node;

typedef struct s_ant
{
	size_t	ant_nb;
	int		room_nb;
}				t_ant;

typedef struct s_paths
{
	struct s_paths	*next;
	t_path_node		*path;
	size_t			path_size;
	size_t			nb_ants;
	size_t			nb_ants2;
	t_ant			*ants;
}				t_paths;

typedef struct s_all_paths_combos {
	int		counter;
	int		size;
	t_paths	**arr;
}	t_all_paths_combos;

typedef struct s_void_list {
	struct s_void_list	*next;
}	t_void_list;

typedef struct s_mlx_win {
	void	*mlx_ptr;
	void	*window;
	size_t	window_width;
	size_t	window_length;
	t_room	*graph;
	size_t	nb_ants;
	t_paths	*optimal_paths;
	size_t	turn_nb;
	size_t	max_turns;
	size_t	scale;
	size_t	margin;
	int		room_color;
	int		background_color;
	char	*start;
	char	*end;
	t_data	*data;
}	t_mlx_win;

typedef struct s_vector {
	size_t	counter;
	size_t	size;
	void	**arr;
}	t_vector;

// Handle error
void		handle_error(void);
void		*handle_null(void *param);

// Utils
size_t		strings_match(char *str1, char *str2);
size_t		get_nb_turns(t_paths *paths);

// List utils
size_t		get_list_size(t_void_list *list);
void		push_front_node(t_path_node **path, t_path_node *path_node);
void		lst_add_in_order(t_paths **paths, t_paths *path_el);

// History functions
int			not_in_history(t_room *node, t_vector *history);

// Path functions
void		print_path_node(t_path_node *path);
void		print_paths(t_paths *paths);
void		set_paths_size(t_paths *paths);
t_paths		*create_path_el(void);
int			create_path_node(t_path_node **path_node, t_room *node);

// Solving functions
int			get_aug_path(t_room *graph, char **start_and_end, \
	t_vector **to_be_visited,t_vector **path);
void		get_paths(t_vector *all_paths_combos, \
	t_room *graph, t_data *data);
void		add_node_to_be_visited(t_room *node, t_room *prev_node, \
	t_vector *to_be_visited);
int			find_best_solution(t_paths **solution, \
	t_vector *all_paths_combos_struct, size_t nb_ants);

// Display result
void		display_result(t_paths *paths, size_t nb_ants);
char		*get_room_name(t_paths *path_ptr, int room_nb);
void		initialize_ants_positions(t_paths *paths);

// Visualizer
void		visualizer(t_room *graph, t_data *data, t_paths *optimal_paths);
void		init_viz(t_room *graph, t_data *data, t_paths *optimal_paths, \
	t_mlx_win **ptr);
void		draw_room(t_mlx_win *mlx_win, t_room *node);
void		draw_rooms(t_mlx_win *mlx_win, t_room *node, t_vector *history);
void		draw_line(t_mlx_win *mlx_win, int *coords_a, int x_b, int y_b);

// Freeing memory
void		free_combos(t_vector *all_paths_combos);
void		free_path_el(t_paths *paths);
void		free_path(t_path_node *path);
void		free_to_be_visited(t_vector **to_be_visited);

// Vectors utils
int			init_vect(t_vector **vector, size_t size);
void		concat_vects(t_vector *src, t_vector **dst);
void		free_vect(t_vector **vector);
void		push_to_vect(t_vector *vector, void *el);

// Handle specific case when start connected to end
void		handle_start_to_end_path2(t_room *graph, t_data *data, \
	t_vector *all_paths_combos);
void		handle_start_to_end_path(t_room *graph, t_data *data, \
	t_vector *all_paths_combos);

void	exit_solver(t_vector *vector, t_data *data);

#endif
