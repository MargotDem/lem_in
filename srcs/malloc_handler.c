/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:54:25 by briffard          #+#    #+#             */
/*   Updated: 2022/10/10 12:37:05 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_data	*create_data(void)
{
	t_data	*element;

	element = (t_data *)malloc(sizeof(*element));
	if (!element)
	{
		panic("In malloc_handler.c: create_data");
		return (NULL);
	}
	return (element);
}

t_room	*new_node(char *line, char letter)
{
	t_room	*new;
	t_room	*element;

	new = (t_room *)malloc(sizeof(*new));
	if (!new)
		return (panic("I malloc_handler: new_node"), NULL);
	element = set_room(line, letter, new);
	if (!element)
	{	
		free(new);
		new = NULL;
	}
	return (element);
}

int	create_hashtable(t_data **data)
{
	size_t			i;
	unsigned long	size;

	i = 0;
	size = (*data)->size_list;
	(*data)->hashtab = (t_room **)malloc(sizeof(*(*data)->hashtab) * size);
	if (!(*data)->hashtab)
		return (panic("In malloc_handler: create_hashtable"), ERROR);
	while (i < size)
	{
		(*data)->hashtab[i] = NULL;
		i++;
	}
	return (TRUE);
}

t_room	**re_alloc(t_room **links, t_room *to, unsigned long size_list)
{
	size_t	x;
	t_room	**dst;

	x = 0;
	dst = (t_room **)malloc(sizeof(t_room *) * size_list + sizeof(t_room *));
	if (!dst)
		return (panic("In malloc_handler: brealloc"), NULL);
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
