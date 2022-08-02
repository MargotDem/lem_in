/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:02:18 by briffard          #+#    #+#             */
/*   Updated: 2022/08/02 09:24:49 by briffard         ###   ########.fr       */
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
	(*data)->size_list += 1;
	(*data)->section_rooms = ACTIVATE;
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
		(*data)->size_list += 1;
		if ((*data)->start_room_name || (*data)->end_room_name)
			clean2str((*data)->start_room_name, (*data)->end_room_name, letter);
		if (letter == 's')
			(*data)->start_room_name = save_name(line);
		else
			(*data)->end_room_name = save_name(line);
		(*data)->section_rooms = ACTIVATE;
		ft_strdel(&line);
	}
}

/*fonction similaire to search_for*/
static int	match(char *room, t_data *data)
{
	t_room	*temp;
	int		index;

	index = hashing(room, data->size_list);
	temp = data->hashtab[index];
	while (temp != NULL)
	{
		if (ft_strcmp(room, temp->name) == 0)
			return (TRUE);
		temp = temp->hash_next;
	}
	return (FALSE);
}

static int	check_link_name(char *line, t_data *data)
{
	int		i;
	char	*room_1;
	char	*room_2;

	room_1 = NULL;
	room_2 = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
		{
			room_1 = ft_strsub(line, 0, i);
			if (match(room_1, data))
			{
				room_2 = ft_strdup(&line[i + 1]);
				if (match(room_2, data))
					return (clean2str(room_1, room_2, 'n'), i);
			}
		}
		i++;
	}
	clean2str(room_1, room_2, 'n');
	return (-1);
}

void	save_links(char *line, t_data **data, t_room **rooms)
{
	char	*link_1;
	char	*link_2;
	int		dash_position;
	t_room	*from;
	t_room	*to;

	(*data)->section_links = ACTIVATE;
	if ((*data)->hashtable_created == FALSE)
		hashtable_main(data, *rooms);
	dash_position = check_link_name(line, *data);
	if (dash_position < 0)
		exit_parsing(line, *rooms, *data);
	link_1 = ft_strsub(line, 0, dash_position);
	link_2 = ft_strdup(&line[dash_position + 1]);
	if (!link_1 || !link_2)
		panic("In save_data.c: save_linker");
	from = search_for(link_1,*data);
	to = search_for(link_2, *data);
	clean2str(link_1, link_2, 'n');
	if (!from || !to)
		exit_parsing(line, *rooms, *data);
	else
		insert_links(from, to);
}
