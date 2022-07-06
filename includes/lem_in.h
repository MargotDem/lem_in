/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:37:29 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/20 11:33:47 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include "mlx.h"
#include "parsing.h"

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

typedef struct s_void_list {
	struct s_void_list	*next;
}	t_void_list;

typedef struct s_coords {
	int	x;
	int	y;
	int	color;
}	t_coords;

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
t_room	*create_node(char *name);
void	print_graph(t_room *node, t_hist *history);
void	find_node(t_room *node, t_hist *history, char *name, t_room **node_to_find);

// List functions
void	lst_add_back(t_void_list *list, t_void_list *new);
void	lst_add_back2(t_void_list **list, t_void_list *new);
size_t	get_list_size(t_void_list *list);
void	remove_from_list(t_void_list **list, t_void_list *node, t_void_list *prev);

// History functions
void	init_history(t_hist **history, int size);
int		not_in_history(t_room *node, t_hist *history);
void	push_history(t_hist *history, t_room *node);
void	pop_history(t_hist *history);
void	reset_history(t_hist *history);
void	print_history(t_hist *history);

// Path functions 1
void	print_path_node(t_path_node *path);
void	print_paths(t_paths *paths);
int		not_in_paths(t_room *node, t_paths **paths);
void	copy_path(t_paths *original, t_paths **copy);
void	set_paths_size(t_paths *paths);

// Path functions 2
void	find_all_paths(t_room *node, t_paths **potential_paths, t_hist *history, char *end);
void	find_optimal_paths(t_room *graph, t_paths **paths, size_t nb_ants, char **start_and_end);
void	select_optimal_paths(t_paths *all_paths, t_paths **paths, size_t nb_ants, char *start, char *end);

// Display result
void	display_result(t_paths *paths, size_t nb_ants);

// Helpers
size_t	strings_match(char *str1, char *str2);

// Test "files"
/*
void	make_graph(t_graph **graph);
void	make_graph2(t_graph **graph);
void	make_graph3(t_graph **graph);
void	make_graph4(t_graph **graph);
void	make_graph5(t_graph **graph);
void	make_graph6(t_graph **graph);
*/

//
void	distribute_ants(t_paths *paths, size_t nb_ants);

// Visualizer
void	visualizer(t_room *graph, size_t nb_ants, t_paths *optimal_paths, char **start_and_end);

char	*get_room_name(t_paths *path_ptr, int room_nb);

#endif
