/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:37:38 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/01 15:37:40 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	get_str_ar_size(char **str_ar)
{
	size_t	size;

	size = 0;
	while (str_ar[size])
		size++;
	return (size);
}

void	free_links(t_links_list **links)
{
	t_links_list	*next;

	if (!links || !(*links))
		return ; // return or handle error?
	while (*links)
	{
		next = (*links)->next;
		free((*links)->name);
		(*links) = next;
	}
}

void	free_rooms(t_rooms_list **rooms)
{
	t_rooms_list	*next;

	if (!rooms || !(*rooms))
		return ; // return or handle error?
	while (*rooms)
	{
		next = (*rooms)->next;
		//deelete the current
		free((*rooms)->name);
		//free_links(&((*rooms)->links_list));
		(*rooms) = next;
	}
	free(*rooms);
}

void	handle_room(t_map *map, char **str_ar, size_t *start, size_t *end, t_rooms_list **rooms)
{
	char			*name;
	t_rooms_list	*room;

	room = (t_rooms_list *)malloc(sizeof(t_rooms_list *));
	if (!(room))
		handle_error();
	name = ft_strdup(str_ar[0]);
	if (!(*rooms))
	{
		(*rooms) = room;
	}
	else
	{
		// add this one to the back.
	}
	room->name = name;
	if (*start)
	{
		*start = 0;
		map->start = ft_strdup(name);
	}
	if (*end)
	{
		*end = 0;
		map->end = ft_strdup(name);
	}
	printf("name: %s\n", name);
}

int	main(void)
{
	char	*line;
	t_rooms_list	*rooms;
	char	**str_ar;
	size_t	ar_size;
	size_t	start;
	size_t	end;
	t_map	*map;

	get_next_line(0, &line);
	printf("heyyy the line now: %s\n", line);
	start = 0;
	end = 0;
	map = (t_map *)malloc(sizeof(t_map *));
	if (!map)
		handle_error();
	map->nb_ants = ft_atoi(line);
	free(line);
	while (get_next_line(0, &line))
	{
		if (*line == '#')
		{
			if (ft_strcmp(line, "##start") == 0 || ft_strcmp(line, "##end") == 0)
			{
				if (ft_strcmp(line, "##start") == 0)
					start = 1;
				else
					end = 1;
				printf("hey start or end\n");
			}
		}
		else
		{
			str_ar = ft_strsplit(line, ' ');
			ar_size = get_str_ar_size(str_ar);

			if (ar_size == 3)
			{
				handle_room(map, str_ar, &start, &end, &rooms);
				printf("room: %s\n", line);
			}
			else
			{
				printf("links: %s\n", line);
			}
			ft_free_str_array(str_ar, ar_size);
				free(str_ar);
		}
		free(line);
	}
	map->rooms = rooms;
	//at the end free everythinggg
	free(map->start);
	free(map->end);
	free(map);
	free_rooms(&rooms);
	system("leaks lem-in");
}

