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

static char	*add_buffer_to(char **str, char *buffer)
{
	char	*temp;

	if (!(*str))
	{
		*str = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
		if (!(*str))
			return (NULL);
		ft_bzero(*str, BUFF_SIZE);
	}
	temp = ft_strjoin(*str, buffer);
	if (!temp)
		return (NULL);
	ft_memdel((void **)(&(*str)));
	*str = temp;
	return (*str);
}

char	*readmap(char *map)
{
	int	ret;
	char	buffer[10000];
	ret = read( 0, buffer, 10000);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		map = add_buffer_to(&map, buffer);
		ret = read(0, buffer, 10000);
	}
	return (map);
}

void    mapreader(t_room **rooms, t_data **data)
{
   unsigned long    ants;
   unsigned short   type;
   char             *line = NULL;
   char				*map;
   int				index;

	(*data)->map = readmap((*data)->map);
	map = (*data)->map;
	ants = get_ants(data,*rooms);
	index = (*data)->index_line;
	while (get_line(&map[index], &line, *data))
	{
		type = type_of_line(line, *data);
		if (type == COMMENT)
		{
			ft_strdel(&line);
			index = (*data)->index_line;
			continue;
		}
		else if (type == EXIT_PARSING)
		{
			ft_strdel(&line);
			exit_parsing(*rooms, *data);
		}
		g_line_dispatch[type](line, data, rooms);
		ft_strdel(&line);
		index = (*data)->index_line;
	}
}