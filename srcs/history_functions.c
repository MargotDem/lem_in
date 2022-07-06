/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:27:02 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/05 17:27:04 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parsing.h"

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
	int	i;
	int	counter;
	int	size;

	counter = history->counter;
	size = history->size;
	if (counter && counter % size == 0)
	{
		print_history(history);
		tmp = (t_room **)malloc(sizeof(t_room *) * (counter + size));
		if (!tmp)
			exit(0); // TODO handle this
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

void	print_history(t_hist *history)
{
	int	k;
	int	counter;

	k = 0;
	counter = history->counter;
	printf("history:\n");
	while (k < counter)
	{
		printf("%s, ", history->arr[k]->name);
		k++;
	}
	printf("\n");
}

void	init_history(t_hist **history, int size)
{
	int	i;

	*history = (t_hist *)malloc(sizeof(t_hist));
	if (!(*history)) // TODO handle this
		exit(0);
	(*history)->size = size;
	(*history)->counter = 0;
	(*history)->arr = (t_room **)malloc(sizeof(t_room *) * size);
	if (!(*history)->arr) // TODO handle this
		exit(0);
	i = 0;
}
