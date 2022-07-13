/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:24:45 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/05 17:24:47 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parsing.h"

t_room	*create_node(char *name)
{
	t_room	*new;

	new = (t_room *)malloc(sizeof(t_room));
	if (new)
	{
		new->links = NULL;
		new->name = name;
		new->nb_links = 0;
	}
	return (new);
}

void	print_graph(t_room *node, t_hist *history, int	only_visited)
{
	size_t	nb_links;
	t_room	**links;
	t_room	*link;
	size_t i;

	nb_links = node->nb_links;
	links = node->links;
	printf("\n");
	if (only_visited && node->visited)
	{
		printf("node: '%s', ", node->name);
		print_history(history);
	}
	i = 0;
	if (not_in_history(node, history))
		push_history(history, node);
	while (i < nb_links)
	{
		link = links[i];
		if (not_in_history(link, history))
			print_graph(link, history, only_visited);
		i++;
	}
}

void	find_node(t_room *node, t_hist *history, char *name, t_room **node_to_find)
{
	size_t	nb_links;
	t_room	**links;
	t_room	*link;
	size_t i;

	if (*node_to_find || !node)
		return ;
	if (strings_match(node->name, name)) // TODO if its the same node you could  pass the node instead of the name and check if same pointer..??
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
			find_node(link, history, name, node_to_find);
		}		
		i++;
	}
}
