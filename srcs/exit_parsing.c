/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:37:11 by briffard          #+#    #+#             */
/*   Updated: 2022/10/07 13:54:24 by briffard         ###   ########.fr       */
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
			rooms = clean_list(rooms);
	handle_error();
	data = data_cleaner(data);
	system("leaks lem-in > exit_p_leaks.txt");
	system("leaks lem-in > exit_leaks.txt");
	exit(EXIT_FAILURE);
}

void	panic(char *message)
{
	perror(message);
}
