/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_functions1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:35:31 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/05 18:35:33 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path_node(t_path_node *path)
{
	while (path)
	{
		ft_putstr(path->node->name);
		if (path->next)
			ft_putstr(", ");
		path = path->next;
	}
	ft_putstr("\n\n");
}

void	print_paths(t_paths *paths)
{
	int	i;

	i = 0;
	while (paths)
	{
		if (paths->nb_ants == 0)
		{
			ft_putstr("\nnot all paths used\n");
			break ;
		}
		ft_putstr("Path ");
		ft_putnbr(i + 1);
		ft_putstr(". Size: ");
		ft_putnbr((int)(paths->path_size));
		ft_putstr(". Number of ants: ");
		ft_putnbr((int)(paths->nb_ants));
		ft_putstr(". Number or turns: ");
		ft_putnbr((int)(paths->nb_ants + paths->path_size - 2));
		ft_putstr("\n");
		print_path_node(paths->path);
		paths = paths->next;
		i++;
	}
}

int	not_in_paths(t_room *node, t_paths **paths)
{
	t_path_node	*path;
	t_paths		*paths_ptr;

	paths_ptr = *paths;
	while (paths_ptr)
	{
		path = paths_ptr->path;
		while (path)
		{
			// TODO not start and end but the actual start and end room
			if (strings_match(node->name, path->node->name) && \
				!strings_match(node->name, "end") && !strings_match(node->name, "start"))
				return (0);
			path = path->next;
		}
		paths_ptr = paths_ptr->next;
	}
	return (1);
}

void	set_paths_size(t_paths *paths)
{
	while (paths)
	{
		paths->path_size = get_list_size((t_void_list *)paths->path);
		paths = paths->next;
	}
}

void	copy_path(t_paths *original, t_paths **copy)
{
	t_paths	*new;

	while (original)
	{
		new = (t_paths *)malloc(sizeof(t_paths));
		new->next = NULL;
		new->path = original->path;
		// if !
		if (!(*copy))
			*copy = new;
		else
			lst_add_back((t_void_list *)*copy, (t_void_list *)new);
		original = original->next;
	}
}
