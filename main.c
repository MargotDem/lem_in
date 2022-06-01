/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:53:51 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/01 15:53:52 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>


typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}				t_btree;

t_btree	*btree_create_node(void *item)
{
	t_btree	*new;

	new = (t_btree *)malloc(sizeof(t_btree));
	if (new)
	{
		new->left = 0;
		new->right = 0;
		new->item = item;
	}
	return (new);
}

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

	(void)cmpf;

	new_node = btree_create_node(item);
	if (new_node)
	{
		cur = *root;
		do_logic(new_node, cur, item, cmpf);
	}
	return (new_node);
}

int	cmp_fct(void *str1, void *str2)
{
	return (ft_strcmp((char *)str1, (char *)str2));
}

t_btree	*insert_node(t_btree **root, char *name)
{
	t_btree		*new_node;

	new_node = btree_insert_data(root, (void *)name, &cmp_fct);
	return (new_node);
}

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root != 0)
	{
		btree_apply_infix(root->left, applyf);
		(*applyf)(root->item);
		btree_apply_infix(root->right, applyf);
	}
}

void	print_tree_node(void *item)
{
	char	*name;

	name = (char *)item;
	printf("name is : '%s'\n", name);
}

void	print_tree(t_btree *root)
{
	btree_apply_infix(root, &print_tree_node);
}

t_btree	*find_room(t_btree *root, char *name)
{
	return (btree_find_node(root, &cmp_fct, (void *)name));
}

int	main(void)
{
	t_btree	*root;
	t_btree	*node_to_find;
	char	*names[4];

	names[0] = "5 first nodeee";
	names[1] = "0 second node";
	names[2] = "8 third node";
	names[3] = "4";


	root = btree_create_node(names[0]);
	int i = 1;
	while (i < 4)
	{
		insert_node(&root, names[i]);
		i++;
	}
	print_tree(root);
	node_to_find = find_room(root, "8 third node");
	printf("\n\n");
	if (node_to_find)
		printf("thats the node to find '%s'\n", (char *)node_to_find->item);
	else
		printf("not found\n");
}
