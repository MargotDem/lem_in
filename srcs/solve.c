/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:14:34 by mde-maul          #+#    #+#             */
/*   Updated: 2022/07/25 21:14:36 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parsing.h"

void	distribute_ants(t_paths *paths, size_t nb_ants)
{
	t_paths	*next;
	t_paths	*paths_ptr;
	int	move;

	if (!paths)
		return ;
	set_paths_size(paths);
	paths->nb_ants = nb_ants;
	paths_ptr = paths;
	while (paths_ptr->next)
	{
		if (paths_ptr == paths)
			move = 0;
		next = paths_ptr->next;
		while (paths_ptr->nb_ants + paths_ptr->path_size - 1 >= next->nb_ants + next->path_size + 1)
		{
			move = 1;
			(paths_ptr->nb_ants)--;
			(next->nb_ants)++;
		}
		if (paths_ptr != paths && next->nb_ants && next->nb_ants + next->path_size == paths_ptr->nb_ants + paths_ptr->path_size - 1)
		{
			move = 1;
			(paths_ptr->nb_ants)--;
			(next->nb_ants)++;
		}
		paths_ptr = next;
		if (!paths_ptr->next && move)
			paths_ptr = paths;
	}
}

t_hist	*get_aug_path(t_room *graph, char *start, char *end, int x)
{
	int	i;
	int	j;
	t_hist	*to_be_visited;
	t_room	**links;
	int		nb_links;
	t_room	*node;
	(void)start; // if start dont schedule right
	(void)x;

	i = 0;
	to_be_visited = NULL;

	init_history(&to_be_visited, 2000);

	while (i < graph->nb_links)
	{
		if (graph->links[i]->reverse == NULL)
		{
			//printf("lets push %s to tobevisited\n", graph->links[i]->name);
			graph->links[i]->to_be_visited = 1;
			push_history(to_be_visited, graph->links[i]);
			init_history(&(graph->links[i]->history), 20);
			push_history(graph->links[i]->history, graph);
		}
		i++;
	}
	i = 0;
	graph->to_be_visited = 1;
	while (i < to_be_visited->counter)
	{
		node = to_be_visited->arr[i];
		//printf("node is %s\n", node->name);
		nb_links = node->nb_links;
		links = node->links;
		j = 0;
		while (j < nb_links)
		{
			if (links[j] == graph) // not sure if this is useful. it gains 0.02 seconds lmao
			{
				j++;
				continue ;
			}
			if (strings_match(links[j]->name, end) && node->reverse == NULL)
			{
				//printf("end reached, from the path: \n");
			
				push_history(node->history, node);
				push_history(node->history, links[j]);
				//print_history(node->history);
				//printf("\n");
				j = 0;
				while (j < to_be_visited->counter)
				{
					to_be_visited->arr[j]->to_be_visited = 0;
					j++;
				}
				return (node->history);
			}

			// the middle condition never happens duh. or does it?? @_@ the brainfuck is real
			if (node->reverse && node->history->arr[node->history->counter - 1]->reverse != node)
			{
				if (node->reverse == links[j])
				{
					links[j]->to_be_visited = 1;
					push_history(to_be_visited, links[j]);
					links[j]->history = NULL;
					append_to_history(node->history, &(links[j]->history));
					push_history(links[j]->history, node);
				}
			}
			else
			{
				if (!links[j]->to_be_visited && links[j]->reverse != node && !strings_match(links[j]->name, end) )
				{
					links[j]->to_be_visited = 1;
					push_history(to_be_visited, links[j]);
					links[j]->history = NULL;
					append_to_history(node->history, &(links[j]->history));
					push_history(links[j]->history, node);
				}
				else if (links[j]->to_be_visited && node->reverse == links[j])
				{
					links[j]->to_be_visited = 1;
					push_history(to_be_visited, links[j]);
					links[j]->history = NULL;
					append_to_history(node->history, &(links[j]->history));
					push_history(links[j]->history, node);
				}
			}

			/*if (!(node->reverse && !(links[j]->reverse) && !(node->history->arr[node->history->counter - 1]->reverse)))
			{
				if (!links[j]->to_be_visited && links[j]->reverse != node && !strings_match(links[j]->name, end) )
				{
					links[j]->to_be_visited = 1;
					push_history(to_be_visited, links[j]);
					links[j]->history = NULL;
					append_to_history(node->history, &(links[j]->history));
					push_history(links[j]->history, node);
				}
				else if (links[j]->to_be_visited && node->reverse == links[j])
				{
					links[j]->to_be_visited = 1;
					push_history(to_be_visited, links[j]);
					links[j]->history = NULL;
					append_to_history(node->history, &(links[j]->history));
					push_history(links[j]->history, node);
				}
			}*/
			j++;
		}
		i++;
	}
	//printf("\n\nno more nodes to visit, gonna return null\n");
	return (NULL);
}

void	push_front(t_path_node **path, t_path_node *path_node)
{
	if (path && path_node)
	{
		path_node->next = *path;
		*path = path_node;
	}
}

void	lst_add_in_order(t_paths **paths, t_paths *path_el)
{
	t_paths	*ptr;
	t_paths	*prev;

	if (path_el)
	{
		if (!(*paths))
			*paths = path_el;
		else
		{
			ptr = *paths;
			prev = NULL;
			while (ptr && path_el->path_size > ptr->path_size)
			{
				prev = ptr;
				ptr = ptr->next;
			}
			if (!prev)
			{
				path_el->next = ptr;
				*paths = path_el;
			}
			else
			{
				path_el->next = ptr;
				prev->next = path_el;
			}
		}
	}
}

static	void	get_paths(t_all_paths_combos *all_paths_combos, t_room *graph, t_data *data)
{
	int	i;
	int	j;
	t_room	*end;
	t_room	*node;
	t_paths *path_el;
	t_paths *paths;
	t_path_node *path_node;
	size_t	path_size;

	i = 0;
	paths = NULL;
	end = search_for(data->exit_room, data);
	while (i < end->nb_links)
	{
		if (end->links[i]->reverse)
		{
			path_el = create_path_el(); //
			
			path_size = 2;
			path_node = (t_path_node *)malloc(sizeof(t_path_node));
			if (!path_node)
				handle_error();
			path_node->next = NULL;
			path_node->node = end;
			path_el->path = path_node;
			j = 0;
			node = end->links[i];
			while (node && node != graph)
			{
				path_size++;
				path_node = (t_path_node *)malloc(sizeof(t_path_node));
				if (!path_node)
					handle_error();
				path_node->next = NULL;
				path_node->node = node;
				//printf("%s, ", node->name);
				push_front(&(path_el->path), path_node);
				node = node->reverse;
			}
			if (node != graph)
				printf("ALERT so here we have a path that ends with a node other than start, this should NEVER happen\n");
			path_node = (t_path_node *)malloc(sizeof(t_path_node));
			if (!path_node)
				handle_error();
			path_node->next = NULL;
			path_node->node = graph;
			push_front(&(path_el->path), path_node);
	
			path_el->path_size = path_size;
			//printf("%s, ", graph->name);

			if (!paths)
				paths = path_el;
			else
				lst_add_in_order(&paths, path_el);
		}
		i++;
		//printf("\n");
	}
	// add to all_paths_combos
	all_paths_combos->arr[all_paths_combos->counter] = paths;
	all_paths_combos->counter++;
}

void	calc_solution(t_paths **solution, t_all_paths_combos *all_paths_combos, size_t nb_ants)
{
	int	k;
	size_t	shortest_nb_turns;

	k = 1; // what if there is not even one path combination???
	distribute_ants(all_paths_combos->arr[0], nb_ants);
	shortest_nb_turns = all_paths_combos->arr[0]->path_size + all_paths_combos->arr[0]->nb_ants;
	*solution = all_paths_combos->arr[0];
	while (k < all_paths_combos->counter)
	{
		distribute_ants(all_paths_combos->arr[k], nb_ants);
		if (all_paths_combos->arr[k]->path_size + all_paths_combos->arr[k]->nb_ants < shortest_nb_turns)
		{
			shortest_nb_turns = all_paths_combos->arr[k]->path_size + all_paths_combos->arr[k]->nb_ants;
			*solution = all_paths_combos->arr[k];
		}
		k++;
	}
}

void	solve222(t_room *graph, t_data *data, char *start, char *end)
{
	t_hist	*path;
	t_all_paths_combos	*all_paths_combos;
	int	x;
	int	i;
	
	t_paths *solution;
	t_paths *solution_tmp;
	(void)solution_tmp;
	size_t	nb_ants;
	size_t	prev_nb_turns;
	char	*start_and_end[2];

	nb_ants = data->ants;
	x = 0;
	prev_nb_turns = 5000;
	all_paths_combos = (t_all_paths_combos *)malloc(sizeof(t_all_paths_combos)); // if null
	all_paths_combos->size = 200;
	all_paths_combos->counter = 0;
	all_paths_combos->arr = (t_paths **)malloc(sizeof(t_paths *) * 200); // same
	while (1)
	{
		path = get_aug_path(graph, start, end, x);
		if (!path)
			break ;
		i = path->counter - 1;
		while (i > 0)
		{
			if (path->arr[i - 1]->reverse && path->arr[i - 1]->reverse != path->arr[i])
			{
				//printf("ALERT so here we are apparently crossing another path...?\n");
			}
			if (path->arr[i - 1]->reverse == path->arr[i])
				path->arr[i - 1]->reverse = NULL;
			else
				path->arr[i]->reverse = path->arr[i - 1];
			i--;
		}
		get_paths(all_paths_combos, graph, data);
		
		// no yeah no. this reduces the time but doesn't find the optimal solution. SAD.
		/*calc_solution(&solution_tmp, all_paths_combos, nb_ants);
		if (prev_nb_turns > solution_tmp->path_size + solution_tmp->nb_ants - 2)
		{
			solution = solution_tmp;
			prev_nb_turns = solution_tmp->path_size + solution_tmp->nb_ants - 2;
		}
		else
			break ;
		*/
		x++;
	}
	calc_solution(&solution, all_paths_combos, nb_ants);
	/*printf("\n\n\n\n\n\n\n\n\nALRIGHTTT\nall paths combos counter is %d", all_paths_combos->counter);
	printf(", and all paths combos is:\n");
	k = 0;
	while (k < all_paths_combos->counter)
	{
		printf("path combination number %d\n\n", k + 1);
		print_paths(all_paths_combos->arr[k]);
		printf("\n");
		k++;
	}
	printf("\n\n\n\n\n\n\n\n");

	*/
	printf("\n");
	display_result(solution, nb_ants);
	if (data->show_paths)
	{
		printf("\n********************\n\nThese are the paths that make up the solution:\n\n");
		print_paths(solution);
		printf("********************\n\n");
		printf("The number of turns is %zu\n\n", solution->path_size + solution->nb_ants - 2);
	}
	if (data->visualizer)
	{
		start_and_end[0] = start;
		start_and_end[1] = end;
		visualizer(graph, nb_ants, solution, start_and_end);
	}
}

void	solve(t_room *graph, t_data *data)
{
	char	*start;
	char	*end;
	t_room	*end_room;

	start = graph->name;
	end = data->exit_room;
	end_room = search_for(end, data);	
	solve222(graph, data, start, end);
}
