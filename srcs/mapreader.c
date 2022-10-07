/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapreader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:36:07 by briffard          #+#    #+#             */
/*   Updated: 2022/10/07 13:21:05 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (FALSE);
		i++;
	}
	if (ft_strchr(line, '-') == NULL)
		return (FALSE);
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
	if (line[0] == '#' && line[1] == '#')
	{
		if (ft_strlen(line) == 7)
		{
			if (ft_strstr(line, "start"))
				return (TRUE);
		}
		else if (ft_strlen(line) == 5)
		{
			if (ft_strstr(line, "end"))
				return (TRUE);
		}
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
		return (COMMENT);
	return (EXIT_PARSING);
}

void	mapreader(t_room **rooms, t_data **data)
{
	unsigned long	ants;
	unsigned short	type;
	char			*line;
	char			*map;
	int				index;

	line = NULL;
	(*data)->map = readmap((*data)->map);
	map = (*data)->map;
	if (!map)
		exit_parsing(line, *rooms, *data);
	ants = get_ants(data, *rooms);
	if (ants == 0)
		exit_parsing(line, *rooms, *data);
	index = (*data)->index_line;
	while (get_line(&map[index], &line, *data))
	{
		type = type_of_line(line, *data);
		if (type == EXIT_PARSING)
			exit_parsing(line, *rooms, *data);
		g_line_dispatch[type](line, data, rooms);
		ft_strdel(&line);
		index = (*data)->index_line;
	}
}
