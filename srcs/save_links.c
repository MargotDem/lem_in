/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:56:55 by briffard          #+#    #+#             */
/*   Updated: 2022/10/10 13:29:44 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	match(char *room, t_data *data)
{
	t_room	*temp;
	int		index;

	index = hashing(room, data->size_list);
	temp = data->hashtab[index];
	while (temp != NULL)
	{
		if (ft_strcmp(room, temp->name) == 0)
			return (TRUE);
		temp = temp->hash_next;
	}
	return (FALSE);
}

static int	check_link_name(char *line, t_data *data)
{
	int		i;
	char	*room_1;
	char	*room_2;

	room_1 = NULL;
	room_2 = NULL;
	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '-')
		{
			room_1 = ft_strsub(line, 0, i);
			if (match(room_1, data))
			{
				ft_strdel(&room_1);
				room_2 = ft_strdup(&line[i + 1]);
				if (match(room_2, data))
					return (ft_strdel(&room_2), i);
				ft_strdel(&room_2);
			}
			ft_strdel(&room_1);
		}
	}
	return (-1);
}

void	save_links(char *line, t_data **data, t_room **rooms)
{
	char	*link_1;
	char	*link_2;
	int		dash_position;
	t_room	*from;
	t_room	*to;

	(*data)->section_links = ACTIVATE;
	if ((*data)->hashtable_created == FALSE)
		hashtable_main(data, *rooms);
	dash_position = check_link_name(line, *data);
	if (dash_position < 0)
		exit_parsing(line, *rooms, *data);
	link_1 = ft_strsub(line, 0, dash_position);
	link_2 = ft_strdup(&line[dash_position + 1]);
	if (!link_1 || !link_2)
	{
		clean2str(link_1, link_2, 'n');
		exit_parsing(line, *rooms, *data);
	}
	from = search_for(link_1, *data);
	to = search_for(link_2, *data);
	clean2str(link_1, link_2, 'n');
	if (!from || !to || !insert_links(from, to))
		exit_parsing(line, *rooms, *data);
}
