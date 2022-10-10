/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_aug_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:21:36 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/10 12:34:37 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reset_to_be_visited(t_vector *to_be_visited)
{
	int	j;
	int	counter;

	j = 0;
	counter = to_be_visited->counter;
	while (j < counter)
	{
		((t_room *)(to_be_visited->arr[j]))->to_be_visited = 0;
		j++;
	}
}

int	init_to_be_visited(t_vector **to_be_visited, t_room *graph)
{
	unsigned int	i;
	t_room			*node;

	i = 0;
	if (!init_vect(to_be_visited, 2000))
		return (ERROR);
	while (i < graph->total_links)
	{
		node = graph->links[i];
		if (!node->reverse)
		{
			node->to_be_visited = 1;
			push_to_vect(*to_be_visited, node);
			if (node->history)
				free_vect(&(node->history));
			if (!init_vect(&(node->history), 20))
				return (ERROR);
			push_to_vect(node->history, graph);
		}
		i++;
	}
	return (OK);
}

void	decide_if_visit(t_room *node, t_room *prev_node, \
	t_vector *to_be_visited, char **start_and_end)
{
	if (prev_node->reverse && \
		((t_room *)(prev_node->history->arr[prev_node->history->counter - \
			1]))->reverse != prev_node)
	{
		if (prev_node->reverse == node)
			add_node_to_be_visited(node, prev_node, to_be_visited);
	}
	else if (\
		(!node->to_be_visited && node->reverse != prev_node && \
			!strings_match(node->name, start_and_end[1])) \
		|| (node->to_be_visited && prev_node->reverse == node))
		add_node_to_be_visited(node, prev_node, to_be_visited);
}

t_vector	*handle_links(t_room *node, t_room *graph, char **start_and_end, \
	t_vector *to_be_visited)
{
	t_room			**links;
	unsigned int	j;

	links = node->links;
	j = 0;
	while (j < node->total_links)
	{
		if (links[j] == graph)
		{
			j++;
			continue ;
		}
		if (strings_match(links[j]->name, start_and_end[1]) \
			&& node->reverse == NULL)
		{
			push_to_vect(node->history, node);
			push_to_vect(node->history, links[j]);
			reset_to_be_visited(to_be_visited);
			return (node->history);
		}
		decide_if_visit(links[j], node, to_be_visited, start_and_end);
		j++;
	}
	return (NULL);
}

int	get_aug_path(t_room *graph, char **start_and_end, \
	t_vector **to_be_visited, t_vector **path)
{
	int			i;
	t_room		*node;

	if (!init_to_be_visited(to_be_visited, graph))
		return (ERROR);
	i = 0;
	while (i < (int)(*to_be_visited)->counter)
	{
		node = (*to_be_visited)->arr[i];
		*path = handle_links(node, graph, start_and_end, *to_be_visited);
		if (*path)
			return (OK);
		i++;
	}
	return (-1);
}
