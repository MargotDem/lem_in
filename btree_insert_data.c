/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:57:15 by mde-maul          #+#    #+#             */
/*   Updated: 2021/09/03 20:52:04 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	do_logic(t_btree *new_node, t_btree *cur, void *item, \
			int (*cmpf)(void *, void *))
{
	t_btree		*prev;
	t_btree		*next;
	int			is_right;

	while (cur != 0)
	{
		if (cmpf(cur->item, item) > 0)
		{
			next = cur->left;
			is_right = 0;
		}
		else
		{
			next = cur->right;
			is_right = 1;
		}
		prev = cur;
		cur = next;
	}
	if (is_right)
		prev->right = new_node;
	else
		prev->left = new_node;
}

t_btree	*btree_insert_data(t_btree **root, void *item, \
			int (*cmpf)(void *, void *))
{
	t_btree		*cur;
	t_btree		*new_node;

	new_node = btree_create_node(item);
	if (new_node)
	{
		cur = *root;
		do_logic(new_node, cur, item, cmpf);
	}
	return (new_node);
}
