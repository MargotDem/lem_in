/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:54:22 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/01 15:54:23 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_graph
{
	struct	s_graph **links;
	char	*name;
	size_t	nb_links;
}				t_graph;

typedef struct s_path
{
	struct s_path	*next;
	t_graph			*node;
}				t_path;

typedef struct s_ant
{
	size_t	ant_nb;
	int	room_nb;
}				t_ant;

typedef struct s_paths
{
	struct s_paths *next;
	t_path *path;
	size_t	path_size;
	size_t	nb_ants;
	size_t	nb_ants2;
	t_ant	*ants;
}				t_paths;

typedef struct s_void_list {
	struct s_void_list	*next;
}	t_void_list;

void	handle_error(void);

// Graph functions
t_graph	*create_node(char *name);
void	print_graph(t_graph *node, t_graph **history);
void	find_node(t_graph *node, t_graph **history, char *name, t_graph **node_to_find);

// List functions
void	lst_add_back(t_void_list *list, t_void_list *new);

// History functions
int		not_in_history(t_graph *node, t_graph **history);
void	push_history(t_graph **history, t_graph *node);
void	pop_history(t_graph **history);
void	reset_history(t_graph **history);
void	print_history(t_graph **history);

// Path functions 1
void	print_path(t_path *path);
void	print_paths(t_paths *paths);
int		not_in_paths(t_graph *node, t_paths **paths);
void	copy_path(t_paths *original, t_paths **copy);
size_t	get_path_size(t_path *path);
void	set_paths_size(t_paths *paths);

// Path functions 2
void	find_potential_paths(t_graph *node, t_paths **potential_paths, t_graph **history, t_paths **paths);
void	find_optimal_paths(t_graph *graph, t_paths **paths, size_t nb_ants);
void	select_optimal_paths(t_paths *all_paths, t_paths **paths, size_t nb_ants);

// Display result
void	display_result(t_paths *paths, size_t nb_ants);

// Helpers
size_t	strings_match(char *str1, char *str2);

// Test "files"
void	make_graph(t_graph **graph);
void	make_graph2(t_graph **graph);
void	make_graph3(t_graph **graph);
void	make_graph4(t_graph **graph);
void	make_graph5(t_graph **graph);

//
void	distribute_ants(t_paths *paths, size_t nb_ants);

#endif
