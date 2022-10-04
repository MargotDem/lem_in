/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:14:09 by briffard          #+#    #+#             */
/*   Updated: 2022/10/04 10:51:36 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_data	*set_data(t_data *node)
{
	node->ants = 0;
	node->help = 0;
	node->visual = 0;
	node->no_map = 0;
	node->print_paths = 0;
	node->end_room_name = NULL;
	node->start_room_name = NULL;
	node->hashtable_created = FALSE;
	node->section_links = DIACTIVATE;
	node->section_rooms = DIACTIVATE;
	node->map = NULL;
	node->index_line = 0;
	node->size_list = 0;
	return (node);
}

t_room	*set_room(char *line, char letter, t_room *room)
{
	room->name = save_name(line);
	if (!room->name)
		panic("In init_value: set_room");
	room->start = FALSE;
	room->end = FALSE;
	room->abscissa = save_abscissa(line);
	room->ordinate = save_ordinate(line);
	room->next = NULL;
	room->hash_next = NULL;
	room->links = NULL;
	if (letter == 's')
		room->start = TRUE;
	else if (letter == 'e')
		room->end = TRUE;
	return (room);
}
