/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:37:11 by briffard          #+#    #+#             */
/*   Updated: 2022/08/05 09:37:07 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

unsigned short	data_is_ok(t_data *data)
{
	t_room	*start;
	t_room	*end;

	if (!data->end_room_name || !data->start_room_name)
		return (FALSE);
	if (!data->hashtab)
		return (FALSE);
	start = search_for(data->start_room_name, data);
	end = search_for(data->end_room_name, data);
	if (data->ants == 0)
		return (FALSE);
	if (start->total_links == 0 || end->total_links == 0)
		return (FALSE);
	return (TRUE);
}

void	exit_parsing(char *line, t_room *rooms, t_data *data)
{
	if (line)
		ft_strdel(&line);
	if (rooms && data->hashtable_created == 0)
		while (rooms != NULL)
			rooms = my_clean(rooms);
	if (data_is_ok(data))
	{
		if (data->no_map == FALSE)
			write(1, data->map, data->index_line);
		printf("go_to_solver\n");
		data = data_cleaner(data);
		system("leaks lem-in");
		exit(EXIT_SUCCESS);
	}
	ft_putstr("ERROR\n");
	data = data_cleaner(data);
	system("leaks lem-in");
	exit(EXIT_FAILURE);
}
