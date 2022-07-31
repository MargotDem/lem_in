#include "parsing.h"

void   save_room(char *line, t_data **data, t_room **room)
{
	t_room  *element;
	element = new_node(line, 'n');
	if (!element)
		panic("malloc a new room");
	*room = push_front(*room, element);
	(*data)->size_list += 1;
	(*data)->section_rooms = ACTIVATE;
}

void	save_command(char *line, t_data **data, t_room **rooms)
{
	t_room	*element;
	char	letter;

	letter = line[2];
	if (letter == 's' || letter == 'e')
	{
		get_next_line(0, &line);
		if (type_of_line(line, *data) != 0)
		{
			ft_strdel(&line);
			exit_parsing(*rooms, *data);
		}
        (*data)->map = cpy_line(line,(*data)->map, *data);
		element = new_node(line, letter);
		*rooms = push_front(*rooms, element);
		(*data)->size_list += 1;
		if (letter == 's')
			(*data)->start_room_name = save_name(line);
		else
			(*data)->end_room_name = save_name(line);
		(*data)->section_rooms = ACTIVATE;
		ft_strdel(&line);
	}
}

/*fonction similaire to search_for*/
static int match(char *room, t_data *data)
{
	t_room *temp;
	int index;

	index = hashing(room, data->size_list);
	temp = data->hashtab[index];
	while (temp != NULL)
	{
		if(ft_strcmp(room, temp->name) == 0)
			return (TRUE);
		temp = temp->hash_next;
	}
	return (FALSE);
}

static int		check_link_name(char *line, t_data *data)
{
	int i;
	char *room_1;
	char *room_2;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
		{
			room_1 = ft_strsub(line, 0 , i);
			if (match(room_1, data))
			{
				room_2 = ft_strdup(&line[i + 1]);
				if (match(room_2, data))
				{
                    clean2str(room_1, room_2);
					return (i);
				}
			}
		}
		i++;
	}
    clean2str(room_1, room_2);
	return (-1);
}

void    save_links(char *line, t_data **data, t_room **rooms)
{
	char *link_1;
	char *link_2;
	int dash_position;
	t_room *from;
	t_room *to;

	(*data)->section_links = ACTIVATE;
	if ((*data)->hashtable_created == FALSE)
		hashtable_main(data, *rooms);
	dash_position = check_link_name(line, *data);
	if (dash_position < 0)
	{
        ft_strdel(&line);
        exit_parsing(*rooms, *data);
    }
	link_1 = ft_strsub(line, 0 , dash_position);
	link_2 = ft_strdup(&line[dash_position + 1]);
	if(!link_1 || !link_2)
		panic("malloc link_1 || link_2");
	from = search_for(link_1,*data);
	to = search_for(link_2, *data);
    clean2str(link_1, link_2);
	if(!from || !to)
        exit_parsing(*rooms, *data);
	else
		insert_links(from, to);	
}