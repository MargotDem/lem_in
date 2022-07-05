#include "parsing.h"

static int command_id(char *line);

static int command_id(char *line)
{
	if ((ft_strcmp(line, "start") != 0) || (ft_strcmp(line, "end") != 0))
			return (1);
	return (0);
}

int is_command(char *line)
{
	if (line[0] == '#' && line[1] == '#')
	{
		if (command_id(&line[2]))
			return (1);
	}
	return(0);
}

void    get_command(t_room **li, char *line, t_data **data)
{
	t_room *element;
	char c;

	c = line[2];
	if (c == 's' || c == 'e')
	{
		while(get_next_line(0, &line)) // What happend if command end pop ?? Should stay with the fisrt command or not??
		{
			if (is_connexion(line, 1))
				go_to_solver(li, line, data);
			if (is_room(line, 0))
				break;
		}
		/*What happend if GNL goes at the end of file*/
		element = new_node(line, c);
		*li = push_t_room(*li, element);
		(*data)->size_lst += 1;
		if (c == 's')
			(*data)->start_room = extract_name(line);
		else
			(*data)->exit_room = extract_name(line);
	}
	(*data)->room_part = 1;
}