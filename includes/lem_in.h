/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:37:29 by mde-maul          #+#    #+#             */
/*   Updated: 2022/07/06 13:46:13 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include "mlx.h"
# include "parsing.h"

typedef struct s_path_node
{
	struct s_path_node	*next;
	t_room			*node;
}				t_path_node;

typedef struct s_ant
{
	size_t	ant_nb;
	int	room_nb;
}				t_ant;

typedef struct s_paths
{
	struct s_paths *next;
	t_path_node *path;
	size_t	path_size;
	size_t	nb_ants;
	size_t	nb_ants2;
	t_ant	*ants;
}				t_paths;

typedef struct s_all_paths_combos {
	int	counter;
	int	size;
	t_paths	**arr;
}	t_all_paths_combos;

typedef struct s_void_list {
	struct s_void_list	*next;
}	t_void_list;

typedef struct s_mlx_win {
	void		*mlx_ptr;
	void		*window;
	size_t		window_width;
	size_t		window_length;
	t_room	*graph;
	size_t	nb_ants;
	t_paths	*optimal_paths;
	size_t	turn_nb;
	size_t	max_turns;
	size_t	scale;
	size_t	margin;
	int	room_color;
	char	**start_and_end;
}	t_mlx_win;

// Handle errors
void	handle_error(void);
void	*handle_null(void *param);

// Graph functions
void	find_node(t_room *node, t_hist *history, char *name, t_room **node_to_find);

// Utils
size_t	strings_match(char *str1, char *str2);
size_t	get_nb_turns(t_paths *paths);
void	print_history(t_hist *history);
void	free_history(t_hist **hist);

// List utils
size_t	get_list_size(t_void_list *list);
void	push_front(t_path_node **path, t_path_node *path_node);
void	lst_add_in_order(t_paths **paths, t_paths *path_el);

// History functions
void	init_history(t_hist **history, int size);
int		not_in_history(t_room *node, t_hist *history);
void	push_history(t_hist *history, t_room *node);
void	pop_history(t_hist *history);
void	copy_history(t_hist *src, t_hist **dst);
void	append_to_history(t_hist *src, t_hist **dst);

// Path functions 1
void	print_path_node(t_path_node *path);
void	print_paths(t_paths *paths);
void	set_paths_size(t_paths *paths);
t_paths	*create_path_el();

// Solving functions
t_hist	*get_aug_path(t_room *graph, char **start_and_end);
void	get_paths(t_all_paths_combos *all_paths_combos, t_room *graph, t_data *data);
void	add_node_to_be_visited(t_room *node, t_room *prev_node, \
	t_hist *to_be_visited);

// Display result
void	display_result(t_paths *paths, size_t nb_ants);
char	*get_room_name(t_paths *path_ptr, int room_nb);

// Distribute ants
void	distribute_ants(t_paths *paths, size_t nb_ants);

// Visualizer
void	visualizer(t_room *graph, size_t nb_ants, t_paths *optimal_paths, char **start_and_end);

#endif
