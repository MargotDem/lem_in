/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:02:18 by briffard          #+#    #+#             */
/*   Updated: 2022/10/05 13:54:25 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	save_room(char *line, t_data **data, t_room **room)
{
	t_room	*element;

	element = new_node(line, 'n');
	if (!element)
		panic("In save_data.c: save_room");
	*room = push_front(*room, element);
	if (!*room)
		exit_parsing(line, *room, *data);
	(*data)->size_list += 1;
	(*data)->section_rooms = ACTIVATE;
}

static void	save_start_end(t_data **data, char letter, char *line)
{
	if (letter == 's')
		(*data)->start_room_name = save_name(line);
	else
		(*data)->end_room_name = save_name(line);
}

void	save_command(char *line, t_data **data, t_room **rooms)
{
	t_room	*element;
	char	letter;
	char	*map;
	int		index;

	map = (*data)->map;
	index = (*data)->index_line;
	letter = line[2];
	if (letter == 's' || letter == 'e')
	{
		get_line(&map[index], &line, *data);
		if (type_of_line(line, *data) != 0)
			exit_parsing(line, *rooms, *data);
		element = new_node(line, letter);
		*rooms = push_front(*rooms, element);
		if (!*rooms)
			exit_parsing(line, *rooms, *data);
		(*data)->size_list += 1;
		if ((*data)->start_room_name || (*data)->end_room_name)
			clean2str((*data)->start_room_name, (*data)->end_room_name, letter);
		save_start_end(data, letter, line);
		(*data)->section_rooms = ACTIVATE;
		ft_strdel(&line);
	}
}
