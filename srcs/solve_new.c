#include "lem_in.h"
#include "parsing.h"

unsigned int	define_solutions(t_data *data, t_room *start)
{
	t_room	*end;
	unsigned int	nb_start;
	unsigned int	nb_end;

	end = search_for(data->exit_room, data);
	nb_start = start->nb_links;
	nb_end = end->nb_links;
	if (nb_start > nb_end)
		return (nb_end);
	return (nb_start);
}

void	copy_cat(t_room *original, t_room **copy)
{
	t_room	*new;

	while (original)
	{
		printf("test--->\n");
		new = (t_room *)malloc(sizeof(t_room));
		new->name = original->name;
		new->next = NULL;
		if (!(*copy))
			*copy = new;
		else
			lst_add_back((t_void_list *)*copy, (t_void_list *)new);
		original = original->next;
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

void	solve_new(t_room *start, t_data *data)
{
	unsigned int	max_solutions;
	t_hist	*to_visit;
	int	i;
	int	j;
	t_room	*node;
	t_room	**links;
	int	nb_links;

	max_solutions = define_solutions(data, start);
	to_visit = NULL;
	init_history(&to_visit, 2000);
	push_history(to_visit, start);

	i = 0;
	while (i < to_visit->counter)
	{
		node = to_visit->arr[i];
		node->next = NULL;
		// printf("hey node is : %s\n", node->name);
		nb_links = node->nb_links;
		links = node->links;
		j = 0;
		while (j < nb_links)
		{
			if (!strings_match(links[j]->name, data->exit_room))
			{
				if (!links[j]->to_be_visited)
				{
					links[j]->to_be_visited = 1;
					push_history(to_visit, links[j]);
					if (node->room_start == 1)
					{
						t_room *new = (t_room *)malloc(sizeof(t_room));
						new->name = node->name;
						new->next = NULL;
						links[j]->history = new;
					}
					// if (!node->history)
					// 	printf("Y A RIEN\n");
					else
					{	copy_cat(node->history,&links[j]->history);
						lst_add_back((t_void_list *)(links[j]->history), (t_void_list *)node);}
					print_lst(links[j]->history);


					//append_to_history(node->history, &(links[j]->history));
					//push_history(links[j]->history, node);
				
				}
			}
			else
			{
				printf("we hav reached the end.\n the history is \n");
				print_lst(node->history);
			}

			j++;
		}
		i++;
	}
}
