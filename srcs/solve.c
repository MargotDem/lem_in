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

void	distribute_ants3(t_paths *paths, size_t nb_ants)
{
	t_paths	*next;
	t_paths	*paths_ptr;

	if (!paths)
		return ;
	set_paths_size(paths);
	paths->nb_ants = nb_ants;
	paths_ptr = paths;
	while (1)
	{
		if (!paths_ptr->next)
			paths_ptr = paths;
		if (!paths_ptr->next) // if this is still the case it means there's only one path
			break ;
		next = paths_ptr->next;
		if (paths_ptr->nb_ants + paths_ptr->path_size - 1 < next->nb_ants + next->path_size + 1)
			break ;
		while (paths_ptr->nb_ants + paths_ptr->path_size - 1 >= next->nb_ants + next->path_size + 1)
		{
			(paths_ptr->nb_ants)--;
			(next->nb_ants)++;
		}
		paths_ptr = next;
	}
}


void	distribute_ants2(t_paths *paths, size_t nb_ants)
{
	t_paths	*next;
	t_paths	*paths_ptr;
	int	move;

	if (!paths)
		return ;
	set_paths_size(paths);
	//printf("size of the first path is %zu\n", paths->path_size);
	paths->nb_ants = nb_ants;
	paths_ptr = paths;
	while (1)
	{
		move = 0;
		if (!paths_ptr->next)
			paths_ptr = paths;
		if (!paths_ptr->next) // if this is still the case it means there's only one path
			break ;
		next = paths_ptr->next;
		/*if (next->path_size == 18)
		{
			printf("YES VIIFHWEFWBEIUBF\n");
			if (paths_ptr->nb_ants + paths_ptr->path_size - 1 < next->nb_ants + next->path_size + 1)
				printf("YES VIIvewvewvwevwevwefewFHWEFWBEIUBF\n");
		}*/
		if (paths_ptr->nb_ants + paths_ptr->path_size - 1 < next->nb_ants + next->path_size + 1)
		{
				//printf("LETS BREEAAKKKK, the first path starts with %s and second starts with %s,\nthe first has %zu ants and second has %zu\n", paths_ptr->path->next->node->name, next->path->next->node->name, paths_ptr->nb_ants, next->nb_ants);

			//break ;
			if (next->nb_ants != 0)
			{
				//paths_ptr = paths;
				//continue ;
				//break ;
				printf("LETS BREEAAKKKK, the first path starts with %s and second starts with %s,\nthe first has %zu ants and second has %zu\n", paths_ptr->path->next->node->name, next->path->next->node->name, paths_ptr->nb_ants, next->nb_ants);
				//break ;
			}
			else
			{
			}
		}
		// not sure if needed now that shortest path fixed
		//while (paths_ptr->nb_ants > 0 && paths_ptr->nb_ants + paths_ptr->path_size - 1 >= next->nb_ants + next->path_size + 1)
		while (paths_ptr->nb_ants + paths_ptr->path_size - 1 >= next->nb_ants + next->path_size + 1)
		{
			move = 1;
			(paths_ptr->nb_ants)--;
			(next->nb_ants)++;
			//paths_ptr = paths;
			//continue ;
		}
		printf("ok so here, the first path starts with %s and second starts with %s,\nthe first has %zu ants and second has %zu\n", paths_ptr->path->next->node->name, next->path->next->node->name, paths_ptr->nb_ants, next->nb_ants);
		paths_ptr = next;
		printf("\n\n");
		if (next->nb_ants == 0)
			break;
		//if (next->nb_ants == 0 && !move)
			//break ;
	}
}

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
			//paths_ptr = paths;
			//continue ;
		}
		paths_ptr = next;
		if (!paths_ptr->next && move)
			paths_ptr = paths;

	}
}

int	calculate_turns(t_room *start, size_t nb_ants, char *end, size_t *new_nb_paths)
{
	int	sol;
	t_paths	*optimal_paths;
	char	*start_and_end[2];

	optimal_paths = NULL;
	start_and_end[0] = start->name;
	start_and_end[1] = end;
	find_optimal_paths2(start, &optimal_paths, nb_ants, start_and_end);
	distribute_ants(optimal_paths, nb_ants);
	*new_nb_paths = get_list_size((t_void_list *)optimal_paths);
	sol = optimal_paths->nb_ants + optimal_paths->path_size - 2;
	return (sol);
}

void	testsolve(t_room *start, size_t nb_ants, char *end)
{
	int	i;
	int	j;
	t_hist	*arr;
	t_hist	*history;
	t_room	*node;
	t_room	**links;
	int	nb_links;
	(void)nb_ants;
	int	prev_sol;
	int	new_sol;
	size_t	new_nb_paths;
	size_t	prev_nb_paths;
	t_paths	*optimal_paths;
	char	*start_and_end[2];

	optimal_paths = NULL;
	start_and_end[0] = start->name;
	start_and_end[1] = end;
	i = 0;
	new_sol = 0;
	prev_sol = 0;
	new_nb_paths = 0;
	prev_nb_paths = 0;
	printf("start\n");
	arr = NULL;
	init_history(&arr, 2000);
	push_history(arr, start);
	start->to_be_visited = 1;
	start->part_of_solution = 1;
	init_history(&(start->history), 50);
	//push_history(start->history, start);
	//while (i < arr->counter && i < 500)
	while (i < arr->counter)
	{
		node = arr->arr[i];
		node->visited = 1;
		nb_links = node->nb_links;
		links = node->links;
		j = 0;
		while (j < nb_links)
		{

				//printf("the child node is %s, mother node is %s\n", links[j]->name, node->name);

			if (!(links[j]->history))
			{
				append_to_history(node->history, &(links[j]->history));
				push_history(links[j]->history, node);
			}
			if (!strings_match(links[j]->name, end))
			{
				if (!links[j]->to_be_visited)
				{
					links[j]->to_be_visited = 1;
					push_history(arr, links[j]);
				}
			}
			else
			{

				printf("end reached from node %s\n", node->name);
				print_history(links[j]->history);
				printf("^ the path to the end ^\n");
				printf("****");
				print_history(arr);
			
				//printf("visited nodes:\n");
				history = NULL;
				//init_history(&history, 2000);
				//print_graph(start, history, 1);

				new_sol = calculate_turns(start, nb_ants, end, &new_nb_paths);
				printf("\nnew sol is %d and prev sol is %d\n", new_sol, prev_sol);
				printf("prev nb paths is %zu and new nb paths is %zu\n", prev_nb_paths, new_nb_paths);
				if (prev_sol == 0 || new_sol < prev_sol)
				{
					prev_sol = new_sol;
					prev_nb_paths = new_nb_paths;
				}
				else if (new_sol == prev_sol && prev_nb_paths < new_nb_paths)
				{
					break ;
				}
				printf("lets break\n");

			}
			j++;
		}

		if (new_sol != 0 && new_sol == prev_sol && prev_nb_paths < new_nb_paths)
		{
			break ;
		}
		i++;
		printf("\n");
	}
	find_optimal_paths2(start, &optimal_paths, nb_ants, start_and_end);
	distribute_ants(optimal_paths, nb_ants);
	printf("\n\n\n\n");
	display_result(optimal_paths, nb_ants);
	printf("nb of turns is %zu\n", optimal_paths->nb_ants + optimal_paths->path_size - 2);
	printf("\n\nTHE OPTIMAL PATHS ARE:\n\n");
	print_paths(optimal_paths);
	printf("\n\nEND OF OPTIMAL PATHS:\n\n");
	visualizer(start, nb_ants, optimal_paths, start_and_end);
}

void solve(t_room *start, t_data *data)
{
	size_t	nb_ants;
	t_hist	*history;
	t_paths	*optimal_paths;
	char	*start_and_end[2];

	nb_ants = data->ants;
	//printf("***** the tree ***** \n");
	history = NULL;
	init_history(&history, 2000);

	testsolve(start, nb_ants, data->exit_room);
	return ;
	//print_graph(start, history, 0);
	//printf("**************\n\n\n");
	printf("HERE before finding optimal paths\n");
	optimal_paths = NULL;
	start_and_end[0] = start->name;
	start_and_end[1] = data->exit_room;
	find_optimal_paths(start, &optimal_paths, nb_ants, start_and_end);
	//printf("\n\nand optimal path the first path nb ants is %zu\n", (optimal_paths)->nb_ants);
	distribute_ants(optimal_paths, nb_ants);
	//printf("and AFTER DISTRIB optimal path the first path nb ants is %zu\n", (optimal_paths)->nb_ants);
	printf("\n\nTHE OPTIMAL PATHS ARE:\n\n");
	print_paths(optimal_paths);
	printf("\n\nEND OF OPTIMAL PATHS:\n\n");
	display_result(optimal_paths, nb_ants);
	printf("nb of turns is %zu\n", optimal_paths->nb_ants + optimal_paths->path_size - 2);
	visualizer(start, nb_ants, optimal_paths, start_and_end);
	printf("\n\n\n\n");
}


/*
new idea
when arriving on node
and checking its children
append history to the history of the child that way the hcild gets all the nodes that lead to it
then when reading end
going thrugh the childs history and setting these nodes to "ispartofsoluion" and find all paths on that data...???

if i can fix these fucking segfaults maybe...?

apres go lire la theorie et c tt pr ajd


ok essayons something else entirely
when you get on a node, you give its children the correct history unless they already have an history
cos it means you can get to this node in a shorter path
when you arrive on end, you add to all paths this history. so for each node you create a path node and BREF
and you do the calculation with allpaths
while new solution is better, continue
normally this way: you get the paths in strict order of shortest to longest
and you stop at the right time
shouldnt take too long with big maps
but it doesnt take into account overlapping paths
but lets try it anyways


*/