/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_find_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:07:05 by mde-maul          #+#    #+#             */
/*   Updated: 2021/12/30 15:07:11 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_find_node(t_btree *btree, int (*f)(void *cur_node_item, \
	void *looked_for_item), void *item)
{
	static t_btree	*found_node;

	if (btree)
	{
		found_node = btree_find_node(btree->left, f, item);
		if (found_node)
			return (found_node);
		if (f(btree->item, item) == 0)
		{
			found_node = btree;
			return (found_node);
		}
		found_node = btree_find_node(btree->right, f, item);
		if (found_node)
			return (found_node);
	}
	return (NULL);
}
