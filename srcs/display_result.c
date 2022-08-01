/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:21:47 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/05 18:21:49 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// can probably be made better
char	*get_room_name(t_paths *path_ptr, int room_nb)
{
	int	i;
	t_path_node	*path;

	i = 0;
	path = path_ptr->path;
	while (i < room_nb)
	{
		path = path->next;
		if (!path)
			return (NULL);
		i++;
	}
	return (path->node->name);
}

void	initialize_ants_positions(t_paths *paths)
{
	t_paths	*paths_ptr;
	size_t	i;

	paths_ptr = paths;
	while (paths_ptr)
	{
		paths_ptr->ants = (t_ant *)malloc(sizeof(t_ant) * paths_ptr->nb_ants);
		if (!(paths_ptr->ants))
			handle_error();
		i = 0;
		while (i < paths_ptr->nb_ants)
		{
			(paths_ptr->ants)[i].room_nb = -i;
			i++;
		}
		paths_ptr = paths_ptr->next;
	}
}

void	initialize_ants_numbers(t_paths *paths, size_t nb_ants)
{
	t_paths	*paths_ptr;
	size_t	i;

	i = 0;
	paths_ptr = paths;
	while (i < nb_ants)
	{
		if (paths_ptr->nb_ants2 < paths_ptr->nb_ants)
		{
			(paths_ptr->ants)[paths_ptr->nb_ants2].ant_nb = i + 1;
			paths_ptr->nb_ants2++;
			i++;
		}
		paths_ptr = paths_ptr->next;
		if (!paths_ptr)
			paths_ptr = paths;
	}
}

void	display_result(t_paths *paths, size_t nb_ants)
{
	t_paths	*paths_ptr;
	size_t	i;
	size_t	movement;

	initialize_ants_positions(paths);
	initialize_ants_numbers(paths, nb_ants);
	while (1)
	{
		movement = 0;
		paths_ptr = paths;
		while (paths_ptr)
		{
			i = 0;
			while (i < paths_ptr->nb_ants)
			{
				(paths_ptr->ants)[i].room_nb++;
				if ((paths_ptr->ants)[i].room_nb > 0 && (paths_ptr->ants)[i].room_nb < (int)paths_ptr->path_size)
				{
					movement = 1;
					ft_putstr("L");
					ft_putnbr((int)((paths_ptr->ants)[i].ant_nb));
					ft_putstr("-");
					ft_putstr(get_room_name(paths_ptr, (paths_ptr->ants)[i].room_nb));
					ft_putstr(" ");
				}
				i++;
			}
			paths_ptr = paths_ptr->next;
		}
		if (!movement)
			break ;
		ft_putstr("\n");
	}
}
