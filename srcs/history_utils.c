/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:27:02 by mde-maul          #+#    #+#             */
/*   Updated: 2022/08/05 08:58:34 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	not_in_history(t_room *node, t_hist *history)
{
	int	i;
	int	counter;

	i = 0;
	if (!history)
		return (1);
	counter = history->counter;
	while (i < counter)
	{
		if (node->name == (history->arr[i])->name)
			return (0);
		i++;
	}
	return (1);
}

void	push_history(t_hist *history, t_room *node)
{
	t_room	**tmp;
	int		i;
	int		counter;
	int		size;

	counter = history->counter;
	size = history->size;
	if (counter && counter % size == 0)
	{
		tmp = (t_room **)handle_null(\
			malloc(sizeof(t_room *) * (counter + size)));
		i = 0;
		while (i < counter)
		{
			tmp[i] = history->arr[i];
			i++;
		}
		i = 0;
		free(history->arr);
		history->arr = tmp;
	}
	history->arr[counter] = node;
	history->counter = history->counter + 1;
}

void	pop_history(t_hist *history)
{
	history->counter = history->counter - 1;
}

void	init_history(t_hist **history, int size)
{
	int	i;

	*history = (t_hist *)handle_null(malloc(sizeof(t_hist)));
	(*history)->size = size;
	(*history)->counter = 0;
	(*history)->arr = (t_room **)handle_null(malloc(sizeof(t_room *) * size));
	i = 0;
}

void	append_to_history(t_hist *src, t_hist **dst)
{
	int	i;
	int	counter;
	int	size;

	i = 0;
	counter = src->counter;
	size = counter;
	if (size == 0)
		size = 50;
	if (!(*dst))
		init_history(dst, size);
	while (i < counter)
	{
		push_history(*dst, src->arr[i]);
		i++;
	}
}
