#include "parsing.h"

static int basic_connexioncheck(char *line, int active_room);
static int shape_connexioncheck(char *line);

static int basic_connexioncheck(char *line, int active_room)
{
	if (active_room == 0)
		return (1);
	if (ft_strchr(line, '-') == NULL)
		return (1);
	return (0);
}

static int shape_connexioncheck(char *line)
{
	int i;

	i = 0;
	// if (recurrence(line, '-'))
	// 	return (1);
	while (line[i] != '\0')
	{
		if (ft_iswhitespace(line[i]))
			return(1);
		i++;
	}
	return (0);
}

int is_connexion(char *line, int active_room)
{
	if (basic_connexioncheck(line, active_room))
		return (0);
	if (shape_connexioncheck(line))
		return (0);
	return (1);
}

int match(char *room, t_data *data)
{
	t_room *temp;
	int index;

	index = hashing(room, data->size_lst);
	temp = data->hashtab[index];
	while (temp != NULL)
	{
		if(ft_strcmp(room, temp->name) == 0)
			return (TRUE);
		temp = temp->h_next;
	}
	return (FALSE);
}

int		test(char *line, t_data *data)
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
					ft_strdel(&room_1);
					ft_strdel(&room_2);
					return (i);
				}
			}
		}
		i++;
	}
	ft_strdel(&room_1);
	ft_strdel(&room_2);
	return (-1);
}



void    get_connexion(t_room **li, char *line, t_data **data)
{
	char *conexion_1;
	char *conexion_2;
	int dash_position;
	t_room *from;
	t_room *to;

	(*data)->connexion_part = 1;
	if ((*data)->hash == 0)
		hashtable_main(data, *li);
	dash_position = test(line, *data);
	if (dash_position < 0)
		go_to_solver(li, line, data);
	//printf("LINE-> %s\n", line);
	conexion_1 = ft_strsub(line, 0 , dash_position);
	conexion_2 = ft_strdup(&line[dash_position + 1]);
	if(!conexion_1 || !conexion_2)
		err_handling("malloc");
	from = search_for(conexion_1,*data);
	to = search_for(conexion_2, *data);
	if(!from || !to)
		go_to_solver(li, line, data);
	else
		insert_links(from, to);
	ft_strdel(&conexion_1);
	ft_strdel(&conexion_2);
}