/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:45:52 by briffard          #+#    #+#             */
/*   Updated: 2022/08/01 13:56:16 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

unsigned short	only_digit_in(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (!ft_isdigit(line[i]))
			return (FALSE);
	}
	return (TRUE);
}

unsigned long	get_ants(t_data **data, t_room *room)
{
	char			*line;
	int				ants;
	char			*map;
	size_t			index;

	index = 0;
	map = (*data)->map;
	while (get_line(&map[index], &line, *data))
	{
		if (only_digit_in(line))
		{
			ants = ft_atoi(line);
			(*data)->ants = ants;
			ft_strdel(&line);
			if (ants == 0 || ants > 1000)
				exit_parsing(line, room, *data);
			return (ants);
		}
		if (type_of_line(line, *data) != 1)
			return (ft_strdel(&line), 0);
		ft_strdel(&line);
		index = (*data)->index_line;
	}
	return (ft_strdel(&line), 0);
}
