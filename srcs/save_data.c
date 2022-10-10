/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:02:18 by briffard          #+#    #+#             */
/*   Updated: 2022/10/10 13:08:14 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	save_room(char *line, t_data **data, t_room **room)
{
	t_room	*element;
	t_room	*li;

	li = NULL;
	element = new_node(line, 'n');
	if (!element)
	{
		panic("In save_data.c: save_room");
		exit_parsing(line, *room, *data);
	}	
	li = push_front(*room, element);
	if (!li)
	{
		ft_strdel(&element->name);
		free(element);
		element = NULL;
		exit_parsing(line, *room, *data);
	}
	*room = li;
	(*data)->size_list += 1;
	(*data)->section_rooms = ACTIVATE;
}

static int	save_start_end(t_data **data, char letter, char *line)
{
	if (letter == 's')
	{
		(*data)->start_room_name = save_name(line);
		if (!(*data)->start_room_name)
			return (ERROR);
	}
	else
	{
		(*data)->end_room_name = save_name(line);
		if (!(*data)->end_room_name)
			return (ERROR);
	}
	return (1);
}

static t_room	*create_command(char *line, char letter, \
				t_room *rooms, t_data *data)
{
	t_room	*element;
	t_room	*temp;

	element = new_node(line, letter);
	temp = push_front(rooms, element);
	if (!temp)
	{
		element = clean_list(element);
		return (NULL);
	}
	rooms = temp;
	data->size_list += 1;
	return (rooms);
}

void	save_command(char *line, t_data **data, t_room **rooms)
{
	t_room	*temp;
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
		temp = create_command(line, letter, *rooms, *data);
		if (!temp)
			exit_parsing(line, *rooms, *data);
		*rooms = temp;
		if ((*data)->start_room_name || (*data)->end_room_name)
			clean2str((*data)->start_room_name, (*data)->end_room_name, letter);
		if (!save_start_end(data, letter, line))
			exit_parsing(line, *rooms, *data);
		(*data)->section_rooms = ACTIVATE;
		ft_strdel(&line);
	}
}
