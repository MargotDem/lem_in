/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:02:34 by briffard          #+#    #+#             */
/*   Updated: 2022/08/01 12:13:18 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_room	*set_copy(t_room *dst, t_room *source)
{
	dst->name = ft_strdup(source->name);
	if (!dst->name)
		panic("In hashtable_malloc: set_copy: dst->name");
	dst->abscisse = source->abscisse;
	dst->ordonne = source->ordonne;
	dst->end = source->end;
	dst->start = source->start;
	dst->total_links = 0;
	dst->hash_next = NULL;
	dst->next = NULL;
	dst->links = (t_room **)malloc(sizeof(t_room *));
	if (!dst->links)
		panic("In hashtable_malloc: set_copy: dst->links");
	return (dst);
}

t_room	*cpy_room(t_room *room)
{
	t_rooom	*element;

	element = (t_room *)malloc(sizeof(t_room));
	if (!element)
		panic("In hashtable_malloc: cpy_room");
	element = set_copy(element, room);
	return (element);
}
