/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_aug_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:21:36 by mde-maul          #+#    #+#             */
/*   Updated: 2022/08/01 18:21:37 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reset_to_be_visited(t_hist *to_be_visited)
{
	int	j;
	int	counter;

	j = 0;
	counter = to_be_visited->counter;
	while (j < counter)
	{
		to_be_visited->arr[j]->to_be_visited = 0;
		j++;
	}
}

void	init_to_be_visited(t_hist **to_be_visited, t_room *graph)
{
	int	i;

	i = 0;
	init_history(to_be_visited, 2000);
	while (i < graph->nb_links)
	{
		if (graph->links[i]->reverse == NULL)
		{
			graph->links[i]->to_be_visited = 1;
			push_history(*to_be_visited, graph->links[i]);
			init_history(&(graph->links[i]->history), 20);
			push_history(graph->links[i]->history, graph);
		}
		i++;
	}
}

void	decide_if_visit(t_room *node, t_room *prev_node, \
	t_hist *to_be_visited, char **start_and_end)
{
	if (prev_node->reverse && \
		prev_node->history->arr[prev_node->history->counter - 1]->reverse \
		!= prev_node)
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

t_hist	*handle_links(t_room *node, t_room *graph, char **start_and_end, \
	t_hist *to_be_visited)
{
	t_room	**links;
	int		j;

	links = node->links;
	j = 0;
	while (j < node->nb_links)
	{
		if (links[j] == graph)
		{
			j++;
			continue ;
		}
		if (strings_match(links[j]->name, start_and_end[1]) \
			&& node->reverse == NULL)
		{
			push_history(node->history, node);
			push_history(node->history, links[j]);
			reset_to_be_visited(to_be_visited);
			return (node->history);
		}
		decide_if_visit(links[j], node, to_be_visited, start_and_end);
		j++;
	}
	return (NULL);
}

void	free_to_be_visited(t_hist **to_be_visited, t_room *node)
{
	int	j;
	int	counter;

	j = 0;
	counter = (*to_be_visited)->counter;
	while (j < counter)
	{
		if ((*to_be_visited)->arr[j] != node && (*to_be_visited)->arr[j]->history)
			free_history(&(*to_be_visited)->arr[j]->history);
		j++;
	}
	free_history(to_be_visited);
}

t_hist	*get_aug_path(t_room *graph, char **start_and_end)
{
	int		i;
	t_hist	*to_be_visited;
	t_hist	*path;
	t_room	*node;

	init_to_be_visited(&to_be_visited, graph);
	i = 0;
	while (i < to_be_visited->counter)
	{
		node = to_be_visited->arr[i];
		path = handle_links(node, graph, start_and_end, to_be_visited);
		if (path)
		{
			free_to_be_visited(&to_be_visited, node);
			return (path);
		}
		i++;
	}
	free_to_be_visited(&to_be_visited, node);
	return (NULL);
}
