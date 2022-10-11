/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:14:09 by briffard          #+#    #+#             */
/*   Updated: 2022/10/05 13:11:12 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_data	*set_data(t_data *node)
{
	node->visual = 0;
	node->help = 0;
	node->no_map = 0;
	node->print_paths = 0;
	node->section_links = DIACTIVATE;
	node->section_rooms = DIACTIVATE;
	node->hashtable_created = FALSE;
	node->ants = 0;
	node->size_list = 0;
	node->hashtab = NULL;
	node->start_room_name = NULL;
	node->end_room_name = NULL;
	node->map = NULL;
	node->index_line = 0;
	return (node);
}

t_room	*set_room(char *line, char letter, t_room *room)
{
	room->name = save_name(line);
	if (!room->name)
		return (panic("In init_value: set_room"), NULL);
	room->start = FALSE;
	room->end = FALSE;
	room->abscissa = save_abscissa(line);
	room->ordinate = save_ordinate(line);
	room->next = NULL;
	room->hash_next = NULL;
	room->links = NULL;
	room->total_links = 0;
	room->to_be_visited = 0;
	room->history = NULL;
	room->reverse = NULL;
	if (letter == 's')
		room->start = TRUE;
	else if (letter == 'e')
		room->end = TRUE;
	room->reverse = NULL;
	room->to_be_visited = 0;
	room->history = NULL;
	return (room);
}
