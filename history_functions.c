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

int	not_in_history(t_graph *node, t_graph **history)
{
	int	i;

	i = 0;
	while (history[i])
	{
		if (node->name == (history[i])->name)
			return (0);
		i++;
	}
	return (1);
}

void	push_history(t_graph **history, t_graph *node)
{
	int	i;

	i = 0;
	while (history[i])
		i++;
	history[i] = node;
}

void	pop_history(t_graph **history)
{
	int	i;

	i = 0;
	while (history[i])
		i++;
	history[i - 1] = NULL;
}

void	reset_history(t_graph **history)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		history[i] = NULL;
		i++;
	}
}

void	print_history(t_graph **history)
{
	int k;

	k = 0;
	printf("history:\n");
	while (history[k])
	{
		printf("%s, ", history[k]->name);
		k++;
	}
	printf("\n");
}
