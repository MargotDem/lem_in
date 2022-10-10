/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:21:47 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/10 12:33:59 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*get_room_name(t_paths *path_ptr, int room_nb)
{
	int			i;
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
	size_t	i;

	while (paths)
	{
		if (!paths->ants)
		{
			paths->ants = (t_ant *)/*handle_null*/(malloc(sizeof(t_ant) * \
				paths->nb_ants));
		}
		i = 0;
		while (i < paths->nb_ants)
		{
			(paths->ants)[i].room_nb = -i;
			i++;
		}
		paths = paths->next;
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

/*char	*build_line(int ant, char *room)
{
	char	*temp;
	char	*tempo;
	char	*nb_int;

	nb_int	= ft_itoa(ant);
	temp = ft_strdup("L");
	tempo = ft_strjoin(temp, nb_int);
	ft_strdel(&temp);
	ft_strdel(&nb_int);
	temp = ft_strjoin(tempo, "-");
	ft_strdel(&tempo);
	tempo = ft_strjoin(temp, room);
	ft_strdel(&temp);
	temp = ft_strjoin(tempo , " ");
	ft_strdel(&tempo);
	return (temp);
}*/

void	handle_ants(t_paths *path_el, size_t *movement)
{
	size_t	i;

	i = 0;
	while (i < path_el->nb_ants)
	{
		(path_el->ants)[i].room_nb++;
		if ((path_el->ants)[i].room_nb > 0 && \
			(path_el->ants)[i].room_nb < (int)path_el->path_size)
		{
			*movement = 1;
			ft_putstr("L");
			ft_putnbr((int)((path_el->ants)[i].ant_nb));
			ft_putstr("-");
			ft_putstr(get_room_name(path_el, (path_el->ants)[i].room_nb));
			ft_putstr(" ");
		}
		i++;
	}
}

void	display_result(t_paths *paths, size_t nb_ants)
{
	t_paths			*paths_ptr;
	size_t			movement;

	initialize_ants_positions(paths);
	initialize_ants_numbers(paths, nb_ants);
	ft_putstr("\n");
	while (1)
	{
		movement = 0;
		paths_ptr = paths;
		while (paths_ptr)
		{
			handle_ants(paths_ptr, &movement);
			paths_ptr = paths_ptr->next;
		}
		if (!movement)
			break ;
		ft_putstr("\n");
	}
}
