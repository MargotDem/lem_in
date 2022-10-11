/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapreader_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:31:05 by briffard          #+#    #+#             */
/*   Updated: 2022/10/07 09:46:44 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*add_buffer_to(char **str, char *buffer)
{
	char	*temp;

	if (!(*str))
	{
		*str = (char *)malloc(sizeof(char) * BUFF_SIZE);
		if (!(*str))
			return (panic("In mapreader_tool: add_buffer_to"), NULL);
		ft_bzero(*str, sizeof(char) * BUFF_SIZE);
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
	int		ret;
	char	buffer[BUFF_SIZE + 1];

	ret = read(0, buffer, BUFF_SIZE);
	if (ret == 0)
		return (NULL);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		map = add_buffer_to(&map, buffer);
		if (!map)
			return (NULL);
		ret = read(0, buffer, BUFF_SIZE);
	}
	return (map);
}

static unsigned int	is_digit(char *line, unsigned int index)
{
	while (line[index] != '\0' && line[index] != ' ')
	{
		if (!ft_isdigit(line[index]))
			return (FALSE);
		index += 1;
	}
	return (index);
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
	i = is_digit(line, i);
	if (i == 0)
		return (FALSE);
	if (line[i] == '\0' || line[i] != ' ' || !ft_isdigit(line[i + 1]))
		return (FALSE);
	i += 1;
	i = is_digit(line, i);
	if (i == 0 || line[i] != '\0')
		return (FALSE);
	return (TRUE);
}

void	pass_comment(char *line, t_data **data, t_room **rooms)
{
	(void)line;
	(void)data;
	(void)rooms;
}
