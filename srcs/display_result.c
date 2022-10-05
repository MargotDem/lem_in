/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:21:47 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/05 13:15:25 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TODO can probably be made better
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
		paths->ants = (t_ant *)handle_null(malloc(sizeof(t_ant) * \
			paths->nb_ants));
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

void	add_ant_nb(size_t ant_nb, t_vector_string *str)
{
	char	c;

	if (ant_nb > 9)
	{
		add_ant_nb(ant_nb / 10, str);
	}
	c = ant_nb % 10 + '0';
	push_to_vect_str(str, c);
}

void	add_room_name(char *name, t_vector_string *str)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(name);
	i = 0;
	while (i < len)
	{
		push_to_vect_str(str, name[i]);
		i++;
	}
}

void	handle_ants(t_paths *path_el, size_t *movement, t_vector_string *str)
{
	(void)str;
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
	t_vector_string	*str;

	initialize_ants_positions(paths);
	initialize_ants_numbers(paths, nb_ants);
	ft_putstr("\n");
	//init_vect_str(&str, 1000);
	str = NULL;
	//push_to_vect_str(str, '\n');
	while (1)
	{
		movement = 0;
		paths_ptr = paths;
		while (paths_ptr)
		{
			handle_ants(paths_ptr, &movement, str);
			paths_ptr = paths_ptr->next;
		}
		if (!movement)
			break ;
		ft_putstr("\n");
		//push_to_vect_str(str, '\n');
	}
	//write(1, str->str, str->counter);
}
