/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:02:34 by briffard          #+#    #+#             */
/*   Updated: 2022/10/07 10:12:17 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_room	*set_copy(t_room *dst, t_room *source)
{
	dst->name = ft_strdup(source->name);
	if (!dst->name)
		return (panic("In hashtable_malloc: set_copy: dst->name"), NULL);
	dst->abscissa = source->abscissa;
	dst->ordinate = source->ordinate;
	dst->end = source->end;
	dst->start = source->start;
	dst->total_links = 0;
	dst->to_be_visited = 0;
	dst->hash_next = NULL;
	dst->next = NULL;
	dst->reverse = NULL;
	dst->history = NULL;
	dst->links = (t_room **)malloc(sizeof(t_room *));
	if (!dst->links)
		return (panic("In hashtable_malloc: set_copy: dst->links"), NULL);
	dst->reverse = NULL;
	dst->to_be_visited = 0;
	dst->history = NULL;
	return (dst);
}

t_room	*cpy_room(t_room *room)
{
	t_room	*element;

	element = (t_room *)malloc(sizeof(t_room));
	if (!element)
		return (panic("In hashtable_malloc: cpy_room"), NULL);
	element = set_copy(element, room);
	if (!element)
		return (NULL);
	return (element);
}
