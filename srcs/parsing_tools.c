/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:08:55 by briffard          #+#    #+#             */
/*   Updated: 2022/10/04 12:19:08 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*save_name(char *line)
{
	size_t	i;
	char	*name;

	i = 0;
	while (line[i] > 32)
		i++;
	name = ft_strsub(line, 0, i);
	if (!name)
		panic("In tools.c: save_name");
	return (name);
}

unsigned int	save_abscissa(char *line)
{
	size_t	i;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	while (line[i] > 32)
		i++;
	return (ft_atoi(&line[i]));
}

unsigned int	save_ordinate(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (ft_isdigit(line[i]))
		i--;
	return (ft_atoi(&line[i]));
}

static int	already_existing_room(t_room *list, t_room *element)
{
	t_room	*temp;

	temp = list;
	while (temp != NULL)
	{
		if (ft_strcmp(element->name, temp->name) == 0)
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

t_room	*push_front(t_room *list, t_room *element)
{
	if (already_existing_room(list, element))
		return (NULL);
	if (list == NULL)
		return (element);
	element->next = list;
	return (element);
}

int	get_line(char *map, char **line, t_data *data)
{
	size_t	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			*line = ft_strsub(map, 0, i);
			i++;
			data->index_line += i;
			return (1);
		}
		i++;
	}
	return (0);
}
