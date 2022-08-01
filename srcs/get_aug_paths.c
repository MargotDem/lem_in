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

t_hist	*get_aug_path(t_room *graph, char **start_and_end)
{
	int	i;
	int	j;
	t_hist	*to_be_visited;
	t_room	**links;
	int		nb_links;
	t_room	*node;

	i = 0;
	to_be_visited = NULL;

	init_history(&to_be_visited, 2000);

	while (i < graph->nb_links)
	{
		if (graph->links[i]->reverse == NULL)
		{
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
		nb_links = node->nb_links;
		links = node->links;
		j = 0;
		while (j < nb_links)
		{
			if (links[j] == graph)
			{
				j++;
				continue ;
			}
			if (strings_match(links[j]->name, start_and_end[1]) && node->reverse == NULL)
			{
				push_history(node->history, node);
				push_history(node->history, links[j]);
				j = 0;
				while (j < to_be_visited->counter)
				{
					to_be_visited->arr[j]->to_be_visited = 0;
					j++;
				}
				return (node->history);
			}
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
				if (!links[j]->to_be_visited && links[j]->reverse != node && !strings_match(links[j]->name, start_and_end[1]) )
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
			j++;
		}
		i++;
	}
	return (NULL);
}
