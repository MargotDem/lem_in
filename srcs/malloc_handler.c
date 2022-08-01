/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:54:25 by briffard          #+#    #+#             */
/*   Updated: 2022/08/01 11:58:41 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_data	*create_data(void)
{
	t_data	*element;

	element = (t_data *)malloc(sizeof(*element));
	if (!element)
		panic("In malloc_handler.c: create_data");
	return (element);
}

t_room	*new_node(char *line, char letter)
{
	t_room	*new;

	new = (t_room *)malloc(sizeof(*new));
	if (!new)
		panic("I malloc_handler: new_node");
	new = set_room(line, letter, new);
	return (new);
}

void	create_hashtable(t_data **data)
{
	size_t			i;
	unsigned long	size;

	i = 0;
	size = (*data)->size_list;
	(*data)->hashtab = (t_room **)malloc(sizeof(*(*data)->hashtab) * size);
	if (!(*data)->hashtab)
		panic("In malloc_handler: create_hashtable");
	while (i < size)
	{
		(*data)->hashtab[i] = NULL;
		i++;
	}
}

t_room	**brealloc(t_room **links, t_room *to, unsigned long size_list)
{
	size_t	x;
	t_room	**dst;

	x = 0;
	dst = (t_room **)malloc(sizeof(t_room *) * size_list + sizeof(t_room *));
	if (!dst)
		panic("In malloc_handler: brealloc");
	while (x < size_list)
	{
		dst[x] = links[x];
		x++;
	}
	dst[x] = to;
	free(links);
	links = NULL;
	return (dst);
}

void	create_links(t_room **room)
{
	(*room)->links = (t_room **)malloc(sizeof(t_room *));
	if (!(*room)->links)
		panic("In malloc_handler: create_links");
	(*room)->links[0] = NULL;
}