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

int	not_in_history(t_room *node, t_vector *history)
{
	int	i;
	int	counter;

	i = 0;
	if (!history)
		return (1);
	counter = history->counter;
	while (i < counter)
	{
		if (node->name == ((t_room *)history->arr[i])->name)
			return (0);
		i++;
	}
	return (1);
}
