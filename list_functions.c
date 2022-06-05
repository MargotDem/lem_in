/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:32:51 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/05 18:32:53 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TODO change this so that if list is not initialized it becomes the new el
void	lst_add_back(t_void_list *list, t_void_list *new)
{
	if (list && new)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

// is this used anywhere
size_t	get_list_size(t_void_list *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}
