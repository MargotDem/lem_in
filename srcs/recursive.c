#include "parsing.h"

void	print_arr(t_room **arr, int size_arr)
{
	int i = 0;

	printf("List node to visite:\n");
	while (i < size_arr)
	{
		printf("\t- %s\n",arr[i]->name);
		i++;
	}
}

void	print_p(t_solver *paths)
{
	int size = paths->valide_chemin;
	int i = 0;
	t_room *temp;


	while(i < size)
	{
		temp = paths->arr[i];
		printf("CHEMIN %d\n", i);
		while(temp->paths_next != NULL)
		{
			printf("\t- %s\n", temp->name);
			temp = temp->paths_next;
		}
		printf("\t- %s\n", temp->name);
		i++;
	}
}

int define_solution(t_room *start, t_room *end)
{
	int	start_nblinks = start->nb_links;
	int	end_nblinks = end->nb_links;

	if (start_nblinks > end_nblinks)
		return (end_nblinks);
	return (start_nblinks);
}

t_solver	*create()
{
	t_solver *element;

	element = (t_solver *)malloc(sizeof(element));
	if (!element)
		err_handling("malloc");
	element->arr = (t_room **)malloc(sizeof(t_room*) * 1);
	if (!element->arr)
		err_handling("malloc");
	element->arr[0] = NULL;
	element->arr_counter = 0;
	element->valide_chemin = 0;

	return (element);
}

void	add_room(t_room *room, t_solver *data)
{
	int arr_size = data->arr_counter;
	int i = 0;
	t_room **dest;

	dest = (t_room **)malloc(sizeof(t_room *) * arr_size + sizeof(t_room *));
	if (!dest)
		err_handling("malloc");
	while (i < arr_size)
	{
		dest[i] = data->arr[i];
		i++;
	}
	dest[i] = room;
	data->arr = dest;
}

void	add_to_visite(t_room *room, t_solver *data)
{
	int	nb_links = room->nb_links;
	int i = 0;
	while (i < nb_links)
	{
		printf("LINKS[%d] --> %s || visited ->%d\n", i, room->links[i]->name, room->links[i]->visited);
		if (room->links[i]->visited == 0)
		{
			printf("Node add to list ->%s\n", room->links[i]->name);
			add_room(room->links[i], data);
			if (room->room_end == 0)
				room->links[i]->visited = 1;
			room->links[i]->parent = room;
			data->arr_counter += 1;
		}
		i++;
	}
}
t_room	*cpy_node(t_room *node)
{
	t_room *cpy;

	cpy = (t_room *)malloc(sizeof(t_room));
	if (!cpy)
		err_handling("malloc");
	cpy->name = node->name;
	cpy->paths_next = NULL;
	cpy->nb_links = node->nb_links;
	cpy->links = node->links;
	cpy->visited = node->visited;
	cpy->room_end = node->room_end;
	cpy->room_start = node->room_start;
	cpy->part_of_solution = node->part_of_solution;
	return (cpy);
}

void	save_paths(t_room *node, t_solver *all_paths)
{
	int arr_size = all_paths->arr_counter;
	int i = 0;
	t_room **dest;
	t_room *cpy;

	cpy = cpy_node(node);

	cpy->paths_next = NULL;
	dest = (t_room **)malloc(sizeof(t_room *) * arr_size + sizeof(t_room *));
	if (!dest)
		err_handling("malloc");
	while (i < arr_size)
	{
		dest[i] = all_paths->arr[i];
		i++;
	}
	dest[i] = cpy;
	all_paths->arr = dest;
}

void	add_node_to_paths(t_room *node, t_solver *all_paths)
{
	int size_arr = all_paths->arr_counter;
	t_room *cpy;

	cpy = cpy_node(node);
	cpy->paths_next = all_paths->arr[size_arr];
	all_paths->arr[size_arr] = cpy;
}

void	reset(t_solver *data)
{
	int size = data->arr_counter;
	int i = 0;

	while (i < size)
	{
		data->arr[i] = NULL;
		i++;
	}
}


void	recursive_solver(t_room *node, int index, t_solver *data, t_solver *all_paths, int max_links)
{
	if (data->nb_links < max_links)
	{
		printf("test\n");
		printf("NODE POSITION ->%s\n", node->name);
		printf("Visited->%d\n", node->visited);
		if (node->room_end == 1)
		{
			node->visited = 0;
			save_paths(node, all_paths);
			printf("<%d>\n", all_paths->arr_counter);
			data->node_ref = node;
			all_paths->valide_chemin += 1;
		}
		else
		{
			add_to_visite(node, data);
			if (index < data->arr_counter)
				recursive_solver(data->arr[index], index + 1, data, all_paths, max_links);
		}
		if (data->node_ref == node)
		{
			printf("CHEMIN -->%s\n", node->name);
			if (node->room_end != 1)
			{
				node->part_of_solution = 1;
				add_node_to_paths(node, all_paths);
			}
			data->node_ref = node->parent;
		}
		else
		{
			if (node->part_of_solution == 0)
				node->visited = 0;
			printf("Node Hors-chemin ->%s || visited ->%d\n", node->name, node->visited);
		}
		if (node->room_start == 1)
		{
			//add_node_to_paths(node, all_paths);
			node->visited = 1;
			all_paths->arr_counter += 1;
			data->nb_links += 1;
			reset(data);
			data->arr_counter = 0;
			recursive_solver(node, 0, data, all_paths, max_links);
		}
	}
}

void test_solver(t_room *start)
{
	int i = 0;
	t_room *temp;
	t_solver *data_solver;
	t_solver *all_paths;

	data_solver = create();
	all_paths = create();
	//add_to_visite(start, data_solver);
	//print_arr(data_solver->arr, data_solver->arr_counter);
	start->visited = 1;
	data_solver->nb_links = 0;
	printf("-->%d\n", data_solver->nb_links);
	recursive_solver(start, 0, data_solver, all_paths, start->nb_links);
	while (i < all_paths->valide_chemin)
	{
		temp = all_paths->arr[i]->paths_next;
		while(temp != NULL)
		{
			printf("NODE TEST-->%s\n", temp->name);
			printf("LINKS = %d\n", temp->nb_links);
			if (temp->room_end == 0)
				recursive_solver(temp, 0, data_solver, all_paths, temp->nb_links);
			data_solver->nb_links = 0;
			temp = temp->paths_next;
		}
		i++;
	}
	print_p(all_paths);
}