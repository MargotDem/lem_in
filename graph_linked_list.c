/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:10:14 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/02 13:10:15 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


typedef struct s_links_list
{
	struct s_graph	*graph_ptr;
	struct s_links_list *next;
}				t_links_list;

typedef struct s_graph
{
	t_links_list *links;
	char	*name;
	size_t	nb_links;
}				t_graph;

static void print_graph(t_graph *node, t_graph **history)
{
	size_t	nb_links;
	t_links_list	*link;

	nb_links = node->nb_links;

	printf("\n");
	printf("'%s', history: \n", node->name);
	int j = 0;
	while (history[j])
	{
		printf("%s, ", (history[j])->name);
		j++;
	}
	printf("\n");
	link = node->links;
	if (not_in_history(node, history))
		push_history(history, node);
	while (link)
	{
		if (not_in_history(link->graph_ptr, history))
		{
			print_graph(link->graph_ptr, history);
			//pop_history(history);
		}
		link = link->next;
	}
}

static void	find_node(t_graph *node, t_graph **history, char *name, t_graph **node_to_find)
{
	t_links_list	*link;

	if (*node_to_find)
		return ;
	if (strings_match(node->name, name))
	{
		*node_to_find = node;
		return ;
	}
	link = node->links;
	if (not_in_history(node, history))
		push_history(history, node);
	while (link)
	{
		if (not_in_history(link->graph_ptr, history))
		{
			find_node(link->graph_ptr, history, name, node_to_find);
		}
		link = link->next;
	}
}

void	links_list_add(t_links_list **list, t_links_list *new)
{
	if (list && new)
	{
		new->next = *list;
		*list = new;
	}
}

void	links_list_add_back(t_links_list **list, t_links_list *new)
{
	if (*list && new)
	{
		while ((*list)->next)
			*list = (*list)->next;
		(*list)->next = new;
	}
	if (!(*list))
	{
		*list = new;
	}
}



void	create_graph(t_graph **graph)
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
	start->links = (t_links_list *)malloc(sizeof(t_links_list));
	start->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	start->links->next->next = (t_links_list *)malloc(sizeof(t_links_list));
	start->links->graph_ptr = A;
	start->links->next->graph_ptr = D;
	start->links->next->next->graph_ptr = F;
	start->links->next->next->next = NULL;

	A->nb_links = 2;
	A->links = (t_links_list *)malloc(sizeof(t_links_list));
	A->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	A->links->graph_ptr = start;
	A->links->next->graph_ptr = B;
	A->links->next->next = NULL;

	B->nb_links = 2;
	B->links = (t_links_list *)malloc(sizeof(t_links_list));
	B->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	B->links->graph_ptr = A;
	B->links->next->graph_ptr = C;
	B->links->next->next = NULL;

	C->nb_links = 3;
	C->links = (t_links_list *)malloc(sizeof(t_links_list));
	C->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	C->links->next->next = (t_links_list *)malloc(sizeof(t_links_list));
	C->links->graph_ptr = B;
	C->links->next->graph_ptr = D;
	C->links->next->next->graph_ptr = end;
	C->links->next->next->next = NULL;

	D->nb_links = 2;
	D->links = (t_links_list *)malloc(sizeof(t_links_list));
	D->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	D->links->graph_ptr = C;
	D->links->next->graph_ptr = start;
	D->links->next->next = NULL;

	F->nb_links = 3;
	F->links = (t_links_list *)malloc(sizeof(t_links_list));
	F->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	F->links->next->next = (t_links_list *)malloc(sizeof(t_links_list));
	F->links->graph_ptr = start;
	F->links->next->graph_ptr = E;
	F->links->next->next->graph_ptr = G;
	F->links->next->next->next= NULL;

	E->nb_links = 2;
	E->links = (t_links_list *)malloc(sizeof(t_links_list));
	E->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	E->links->graph_ptr = F;
	E->links->next->graph_ptr = H;
	E->links->next->next = NULL;

	G->nb_links = 2;
	G->links = (t_links_list *)malloc(sizeof(t_links_list));
	G->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	G->links->graph_ptr = F;
	G->links->next->graph_ptr = I;
	G->links->next->next = NULL;

	I->nb_links = 2;
	I->links = (t_links_list *)malloc(sizeof(t_links_list));
	I->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	I->links->graph_ptr = G;
	I->links->next->graph_ptr = H;
	I->links->next->next = NULL;

	H->nb_links = 3;
	H->links = (t_links_list *)malloc(sizeof(t_links_list));
	H->links->next = (t_links_list *)malloc(sizeof(t_links_list));
	H->links->next->next = (t_links_list *)malloc(sizeof(t_links_list));
	H->links->graph_ptr = end;
	H->links->next->graph_ptr = E;
	H->links->next->next->graph_ptr = I;
	H->links->next->next->next= NULL;

	*graph = start;
}

void	create_graph2(t_graph **graph)
{
	char	*links[13] = {
		"start-A",
		"start-D",
		"start-F",
		"A-B",
		"B-C",
		"C-D",
		"C-end",
		"F-E",
		"F-G",
		"E-H",
		"G-I",
		"I-H",
		"H-end",
	};

	char	*dash_ptr;
	char	*room_str;
	char	*first_room_name;
	char	*second_room_name;
	int		i;
	t_graph	*history[100];
	
	t_graph	*first_room = NULL;
	t_graph	*second_room = NULL;
	t_links_list *link_first_room;
	t_links_list *link_second_room;

	reset_history(history);

	//init treee
	room_str = links[0];
	dash_ptr = ft_strchr(room_str, '-');
	first_room_name = ft_strsub(room_str, 0, dash_ptr - room_str);
	*graph = create_node(first_room_name);
	free(first_room_name);
	printf("***** the tree with just one node in it***** \n");
	print_graph(*graph, history);
	printf("******\n");
	reset_history(history);
	i = 0;
	while (i < 13)
	{
		if (i == 3)
		{
			printf("by then starts links should be A D and F: \n");
			t_links_list *list = (*graph)->links;
			while (list)
			{
				printf("node: %s, ", list->graph_ptr->name);
				list = list->next;
			}
			printf("\n\n");
		}
		// find the - char in the link string
		room_str = links[i];
		dash_ptr = ft_strchr(room_str, '-');
		//if ! dashptr
		second_room_name = dash_ptr + 1;
		first_room_name = ft_strsub(room_str, 0, dash_ptr - room_str);


		// if first room is in tree
		first_room = NULL;
		find_node(*graph, history, first_room_name, &first_room);
		reset_history(history);
		if (!first_room)
		{
			printf("i is %d, first room not found so creaeting\n", i);
			first_room = create_node(first_room_name);
		}
		
		second_room = NULL;
		find_node(*graph, history, second_room_name, &second_room);
		reset_history(history);
		if (!second_room)
		{
			printf("i is %d, second room not found so creaeting\n", i);
			second_room = create_node(second_room_name);
		}

		printf("first room str is %s, and node %s\n", first_room_name, first_room->name);
		printf("second room str is %s, and node %s\n", second_room_name, second_room->name);
		
		link_first_room = (t_links_list *)malloc(sizeof(link_first_room));
		//if !
		link_first_room->next = NULL;
		link_first_room->graph_ptr = second_room;
		
		link_second_room = (t_links_list *)malloc(sizeof(link_second_room));
		//if !
		link_second_room->next = NULL;
		link_second_room->graph_ptr = first_room;

		links_list_add(&(first_room->links), link_first_room);
		links_list_add(&(second_room->links), link_second_room);
		
		i++;
		free(first_room_name);
		printf("\n\n");
	}
}

void graph_linked_list(void)
{
	t_graph	*graph;
	t_graph	*history[100];
	reset_history(history);

	//create_graph(&graph);
	create_graph2(&graph);
	
	printf("***** the tree***** \n");
	print_graph(graph, history);
	reset_history(history);
	printf("******\n");

	t_graph *node_to_find = NULL;
	find_node(graph, history, "H", &node_to_find);
	if (node_to_find)
		printf("thats the node '%s'\n", node_to_find->name);
	else
		printf("not found\n");

}

