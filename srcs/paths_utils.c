/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:35:31 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/10 12:37:27 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths	*create_path_el(void)
{
	t_paths	*path_el;

	path_el = (t_paths *)(malloc(sizeof(t_paths)));
	if (!path_el)
		return (NULL);
	ft_bzero((void *)path_el, sizeof(t_paths));
	return (path_el);
}

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

void	set_paths_size(t_paths *paths)
{
	while (paths)
	{
		paths->path_size = get_list_size((t_void_list *)paths->path);
		paths = paths->next;
	}
}
