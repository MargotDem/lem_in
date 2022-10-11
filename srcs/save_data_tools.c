/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:07:41 by briffard          #+#    #+#             */
/*   Updated: 2022/10/07 13:25:42 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	links_already_exist(t_room *room_1, t_room *room_2)
{
	int	index;
	int	max;

	index = 0;
	max = room_1->total_links;
	while (index < max)
	{
		if (ft_strcmp(room_1->links[index]->name, room_2->name) == 0)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

int	create_link(t_room *room_1, t_room *room_2)
{
	if (room_1->links[0] == NULL)
	{
		room_1->links[0] = room_2;
		room_1->total_links = 1;
	}
	else
	{
		room_1->links = re_alloc(room_1->links, room_2, room_1->total_links);
		room_1->total_links += 1;
	}
	if (!room_1->links)
		return (ERROR);
	return (TRUE);
}

int	insert_links(t_room *from, t_room *to)
{
	if (!links_already_exist(from, to))
	{
		if (!create_link(to, from))
			return (ERROR);
		if (!create_link(from, to))
			return (ERROR);
	}
	return (TRUE);
}
