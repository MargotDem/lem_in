/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_to_be_visited.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:21:39 by mde-maul          #+#    #+#             */
/*   Updated: 2022/08/02 15:21:40 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_node_to_be_visited(t_room *node, t_room *prev_node, \
	t_vector *to_be_visited)
{
	node->to_be_visited = 1;
	push_to_vect(to_be_visited, node);
	if (node->history)
		free_vect(&(node->history));
	concat_vects(prev_node->history, &(node->history));
	push_to_vect(node->history, prev_node);
}
