/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:19:17 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/04 17:19:19 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

typedef struct s_graph
{
	struct s_graph **links;
	char	*name;
	size_t	nb_links;
}				t_graph;

typedef struct s_path
{
	struct s_path *next;
	t_graph *node;
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
	size_t	nb_turns;
	t_ant	*ants;
	size_t	first_ant_nb;
}				t_paths;


t_graph	*create_node(char *name);
int	not_in_history(t_graph *node, t_graph **history);
void	push_history(t_graph **history, t_graph *node);
void	reset_history(t_graph **history);

static void print_graph(t_graph *node, t_graph **history)
{
	size_t	nb_links;
	t_graph	**links;
	t_graph	*link;
	size_t i;

	nb_links = node->nb_links;
	links = node->links;
	printf("\n");
	printf("'%s', history: \n", node->name);
	int j = 0;
	while (history[j])
	{
		printf("%s, ", (history[j])->name);
		j++;
	}
	printf("\n");
	i = 0;
	if (not_in_history(node, history))
		push_history(history, node);
	while (i < nb_links)
	{
		link = links[i];
		if (not_in_history(link, history))
		{
			print_graph(link, history);
			//pop_history(history);
		}
		i++;
	}
}

void	find_nodee(t_graph *node, t_graph **history, char *name, t_graph **node_to_find)
{
	size_t	nb_links;
	t_graph	**links;
	t_graph	*link;
	size_t i;

	if (*node_to_find)
		return ;
	if (ft_strcmp(node->name, name) == 0)
	{
		*node_to_find = node;
		return ;
	}
	nb_links = node->nb_links;
	links = node->links;
	if (not_in_history(node, history))
		push_history(history, node);
	i = 0;
	while (i < nb_links)
	{
		link = links[i];
		if (not_in_history(link, history))
		{
			find_nodee(link, history, name, node_to_find);
		}		
		i++;
	}
}

void	make_graph(t_graph **graph)
{
	t_graph	*start;
	t_graph	*A;
	t_graph	*B;
	t_graph	*C;
	t_graph	*D;
	t_graph	*E;
	t_graph	*F;
	t_graph	*G;
	t_graph	*H;
	t_graph	*I;
	t_graph	*end;
	
	start = create_node("start");
	A = create_node("A");
	B = create_node("B");
	C = create_node("C");
	D = create_node("D");
	E = create_node("E");
	F = create_node("F");
	G = create_node("G");
	H = create_node("H");
	I = create_node("I");
	end = create_node("end");

	start->nb_links = 3;
	start->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	start->links[0] = A;
	start->links[1] = D;
	start->links[2] = F;

	A->nb_links = 2;
	A->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	A->links[0] = start;
	A->links[1] = B;

	B->nb_links = 2;
	B->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	B->links[0] = A;
	B->links[1] = C;

	C->nb_links = 3;
	C->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	C->links[0] = B;
	C->links[1] = D;
	C->links[2] = end;

	D->nb_links = 2;
	D->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	D->links[0] = C;
	D->links[1] = start;

	F->nb_links = 3;
	F->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	F->links[0] = start;
	F->links[1] = E;
	F->links[2] = G;

	E->nb_links = 2;
	E->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	E->links[0] = F;
	E->links[1] = H;

	G->nb_links = 2;
	G->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	G->links[0] = F;
	G->links[1] = I;

	I->nb_links = 2;
	I->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	I->links[0] = G;
	I->links[1] = H;

	H->nb_links = 3;
	H->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	H->links[0] = end;
	H->links[1] = E;
	H->links[2] = I;

	*graph = start;
}

void	make_graph2(t_graph **graph)
{
	t_graph	*start;
	t_graph	*A;
	t_graph	*B;
	t_graph	*end;
	
	start = create_node("start");
	A = create_node("2");
	B = create_node("3");
	end = create_node("end");

	start->nb_links = 1;
	start->links = (t_graph **)malloc(sizeof(t_graph *) * 1);
	start->links[0] = A;

	A->nb_links = 2;
	A->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	A->links[0] = start;
	A->links[1] = B;

	B->nb_links = 2;
	B->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	B->links[0] = A;
	B->links[1] = end;

	end->nb_links = 1;
	end->links = (t_graph **)malloc(sizeof(t_graph *) * 1);
	end->links[0] = B;

	*graph = start;
}

void	make_graph3(t_graph **graph)
{
	t_graph	*start;
	t_graph	*A;
	t_graph	*B;
	t_graph	*C;
	t_graph	*end;
	
	start = create_node("start");
	A = create_node("1");
	B = create_node("3");
	C = create_node("2");
	end = create_node("end");

	start->nb_links = 2;
	start->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	start->links[0] = A;
	start->links[1] = C;

	A->nb_links = 2;
	A->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	A->links[0] = start;
	A->links[1] = end;

	B->nb_links = 2;
	B->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	B->links[0] = C;
	B->links[1] = end;

	C->nb_links = 2;
	C->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	C->links[0] = start;
	C->links[1] = B;

	end->nb_links = 2;
	end->links = (t_graph **)malloc(sizeof(t_graph *) * 1);
	end->links[0] = A;
	end->links[1] = B;

	*graph = start;
}

void	paths_list_add_back(t_paths *list, t_paths *new)
{
	if (list && new)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

void	path_list_add_back(t_path *list, t_path *new)
{
	if (list && new)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

void	pop_history(t_graph **history)
{
	int	i;

	i = 0;
	while (history[i])
		i++;
	history[i - 1] = NULL;
}

void	print_history(t_graph **history)
{
	int k = 0;
	printf("the history:\n");
	while (history[k])
	{
		printf("%s, ", history[k]->name);
		k++;
	}
	printf("\n\n");
}

void	print_path(t_path *path)
{
	printf("the path:\n");
	while (path)
	{
		printf("%s, ", path->node->name);
		path = path->next;
	}
	printf("\n\n");
}

void	print_paths(t_paths *paths)
{
	while (paths)
	{
		printf("path size is %zu, nb of ants is %zu, ", paths->path_size, paths->nb_ants);
		print_path(paths->path);
		paths = paths->next;
	}
	printf("\n\n");
}

int     not_in_shortest_paths(t_graph *node, t_paths **paths)
{
	t_path  *path;
	t_paths  *paths_ptr;
	paths_ptr = *paths;
   while (paths_ptr)
   {
       path = (paths_ptr)->path;
       while (path)
       {
           if (ft_strcmp(node->name, path->node->name) == 0 && \
		   		ft_strcmp(node->name, "end") && ft_strcmp(node->name, "start"))
			{
               return (0);
			}
           path = path->next;
       }
       paths_ptr = (paths_ptr)->next;
   }
   return (1);
}


void	find_potential_paths(t_graph *node, t_paths **potential_paths, t_graph **history, t_paths **paths)
{
	size_t	nb_links;
	t_graph	**links;
	t_graph	*link;
	size_t i;
	

	nb_links = node->nb_links;
	links = node->links;

	//printf("here\n");
	
	if (ft_strcmp(node->name, "end") == 0)
	{
		// add the history plus end to the potential paths linked list
		
		size_t j;
		j = 0;
		t_paths	*path_el;
		t_path	*node;
		t_path	*path;
	
		path_el = (t_paths *)malloc(sizeof(t_paths));
		//if !
		path_el->next = NULL;
		path_el->path = NULL;
		path_el->path_size = 0;

		path = NULL;
		while (history[j])
		{
			node = (t_path *)malloc(sizeof(t_path));
			//if !
			node->next = NULL;
			node->node = history[j];
			if (!path)
				path = node;
			else
				path_list_add_back(path, node);
			j++;
		}
		path_el->path = path;
		if (!(*potential_paths))
			*potential_paths = path_el;
		else
			paths_list_add_back(*potential_paths, path_el);
		return ;
	}
	i = 0;
	
	while (i < nb_links)
	{
		//printf("ah que coucou\n");
		link = links[i];
		if (not_in_history(link, history) && not_in_shortest_paths(link, paths))
		{
			//printf("not in histo\n");
			push_history(history, link);
			find_potential_paths(link, potential_paths, history, paths);
			pop_history(history);
		}
		i++;
	}
}

size_t	get_path_size(t_path *path)
{
	size_t	i;

	i = 0;
	while (path)
	{
		i++;
		path = path->next;
	}
	return (i);
}

void	copy_path(t_paths *original, t_paths **copy)
{
	t_paths	*new;

	while (original)
	{
		new = (t_paths *)malloc(sizeof(t_paths));
		new->next = NULL;
		new->path = original->path;
		// if !
		if (!(*copy))
			*copy = new;
		else
			paths_list_add_back(*copy, new);
		original = original->next;
	}
}

size_t	get_list_size(t_paths *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	find_shortest_path(t_graph *graph, t_paths **paths)
{
	t_paths	*potential_paths;
	t_paths	*t_paths_ptr;
	t_graph	*history[100];
	t_paths	*shortest;
	size_t	shortest_size;
	int	i;

	while (1)
	{
		// search shortest
		reset_history(history);
		push_history(history, graph);
		potential_paths = NULL;
		find_potential_paths(graph, &potential_paths, history, paths);
		if (!potential_paths)
			break ;
		t_paths_ptr = potential_paths;
		// !!!! if nulll
		shortest = t_paths_ptr;
		shortest_size = get_path_size(shortest->path);
		i = 1;
		while (t_paths_ptr)
		{
			if (get_path_size(t_paths_ptr->path) < shortest_size)
				shortest = t_paths_ptr;
			t_paths_ptr = t_paths_ptr->next;
			i++;
		}

		//copy_path(shortest, &shortest_copy);
		// instead of doing this, dont forget to free the other ones from potential paths ie up until shortest and after shortest
		shortest->next = NULL;

		// from all the potential paths, find the shortest one
		// and add it to paths linked list
		if (!(*paths))
			*paths = shortest;
		else
			paths_list_add_back(*paths, shortest);
	}
}

void	set_paths_size(t_paths *paths)
{
	while (paths)
	{
		paths->path_size = get_path_size(paths->path);
		paths = paths->next;
	}
}


int	get_nb_turns(t_paths *path)
{
	return (path->nb_ants + path->path_size - 2);
}

void	distribute_ants(t_paths *paths, size_t nb_ants)
{
	t_paths	*next;

	paths->nb_ants = nb_ants;
	while (paths->next)
	{
		next = paths->next;
		next->nb_ants = 0;
		while (paths->nb_ants - 1 + paths->path_size >= next->nb_ants + 1 + next->path_size)
		{
			(paths->nb_ants)--;
			(next->nb_ants)++;
		}
		paths = next;
	}
}

char	*get_room_name(t_paths *path_ptr, int room_nb)
{
	int	i;
	t_path	*path;

	i = 0;
	path = path_ptr->path;
	while (i < room_nb)
	{
		path = path->next;
		i++;
	}
	return (path->node->name);
}

void	display_result(t_paths *paths, size_t nb_ants)
{
	t_paths	*paths_ptr;
	size_t	i;
	size_t	movement;
	size_t	first_ant_nb;

	paths_ptr = paths;
	first_ant_nb = 0;
	while (paths_ptr)
	{
		paths_ptr->nb_ants2 = 0;
		paths_ptr->ants = (t_ant *)malloc(sizeof(t_ant) * paths_ptr->nb_ants);
		i = 0;
		while (i < paths_ptr->nb_ants)
		{
			(paths_ptr->ants)[i].room_nb = -i;
			(paths_ptr->ants)[i].ant_nb = i + 1 + first_ant_nb;
			i++;
		}
		paths_ptr->first_ant_nb = first_ant_nb;
		first_ant_nb += paths_ptr->nb_ants;
		paths_ptr = paths_ptr->next;
	}

	// set ants' names
	i = 0;
	paths_ptr = paths;
	while (i < nb_ants)
	{
		if (paths_ptr->nb_ants2 < paths_ptr->nb_ants)
		{
			(paths_ptr->ants)[paths_ptr->nb_ants2].ant_nb = i + 1;
			paths_ptr->nb_ants2++;
		}
		paths_ptr = paths_ptr->next;
		if (!paths_ptr)
			paths_ptr = paths;
		i++;
	}

	while (1)
	{
		movement = 0;
		paths_ptr = paths;
		while (paths_ptr)
		{
			i = 0;
			while (i < paths_ptr->nb_ants)
			{
				(paths_ptr->ants)[i].room_nb++;
				if ((paths_ptr->ants)[i].room_nb > 0 && (paths_ptr->ants)[i].room_nb < (int)paths_ptr->path_size)
				{
					movement = 1;
					printf("L%zu-%s", (paths_ptr->ants)[i].ant_nb, get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb));
					printf(" ");
				}
				i++;
			}
			paths_ptr = paths_ptr->next;
		}
		printf("\n");
		if (!movement)
			break ;
	}
}

void	solve(t_graph *graph, size_t nb_ants)
{
	t_paths	*paths;

	paths = NULL;

	// find abs shortest path
	find_shortest_path(graph, &paths);

	printf("\n\nSMALLEST PATHS ARE:\n\n");
	set_paths_size(paths);
	// decide how many ants go where
	distribute_ants(paths, nb_ants);
	print_paths(paths);
	// display the solution

	display_result(paths, nb_ants);
}

void graph_array(void)
{
	t_graph	*graph;
	size_t	nb_ants;
	
	t_graph	*history[100];
	
	reset_history(history);

	make_graph(&graph);
	
	printf("***** the tree***** \n");
	print_graph(graph, history);
	reset_history(history);
	printf("******\n\n\n");

	/*
	t_graph *node_to_find = NULL;
	find_nodee(graph, history, "I", &node_to_find);
	reset_history(history);
	if (node_to_find)
		printf("thats the nodeee '%s'\n", node_to_find->name);
	else
		printf("not found\n");
	*/

	nb_ants = 10;
	solve(graph, nb_ants);

	
}
