#include "parsing.h"

unsigned short	is_link(char *line, unsigned short section_rooms)
{
	size_t	i;

	i = 0;
	if (section_rooms == DIACTIVATE)
		return (FALSE);
	while (line[i] != '\0')
	{
		if (ft_iswhitespace(line[i]))
			return(FALSE);
		i++;
	}
	if (ft_strchr(line, '-') == NULL)
		return (FALSE);
	return (TRUE);
}

unsigned short	is_room(char *line, unsigned short section_links)
{
	char	letter;
	size_t	i;

	i = 0;
	letter = line[0];
	if (section_links == ACTIVATE)
		return (FALSE);
	if (letter == '#' || letter == 'L' || letter < 33)
		return (FALSE);
	while (line[i] > 32 && line[i] != '\0')
			i++;
	if (line[i] == '\0' || line[i] != ' ' || !ft_isdigit(line[i + 1]))
		return (FALSE);
	i += 1;
	while (line[i] != '\0' && line[i] != ' ')
	{
		if (!ft_isdigit(line[i]))
			return (FALSE);
		i++;
	}
	if (line[i] == '\0' || line[i] != ' ' || !ft_isdigit(line[i + 1]))
		return (FALSE);
	i += 1;
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

unsigned short	is_comment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (TRUE);
	return (FALSE);
}

unsigned short	is_command(char *line)
{
	char	*test;
	if (line[0] == '#' && line[1] == '#')
	{
		test = &line[2];
		if ((ft_strcmp(test, "start") != 0) || (ft_strcmp(test, "end") != 0))
			return(TRUE);		
	}
	return (FALSE);
}

unsigned short	type_of_line(char *line, t_data *data)
{
	if (is_room(line, data->section_links))
		return (ROOMS);
	if (is_command(line))
		return (COMMAND);
	if (is_link(line, data->section_rooms))
		return (LINKS);
	if (is_comment(line))
		return(COMMENT);
	return (EXIT_PARSING);
}

void    mapreader(t_room **rooms, t_data **data)
{
   unsigned long    ants;
   unsigned short   type;
   char             *line;

	ants = get_ants(data);
	if (ants == 0)
		exit_parsing(*rooms, *data);
	while (get_next_line(0, &line) > 0)
	{
		type = type_of_line(line, *data);
		(*data)->map = cpy_line(line,(*data)->map, *data);
		if (type == COMMENT)
		{
			ft_strdel(&line);
			continue;
		}
		else if (type == EXIT_PARSING)
		{
			ft_strdel(&line);
			exit_parsing(*rooms, *data);
		}
		g_line_dispatch[type](line, data, rooms);
		ft_strdel(&line);
	}
}