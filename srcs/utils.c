/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:50:58 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/05 18:51:01 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	strings_match(char *str1, char *str2)
{
	if (ft_strcmp(str1, str2) == 0)
		return (1);
	return (0);
}

size_t	get_nb_turns(t_paths *paths)
{
	return (paths->path_size + paths->nb_ants - 2);
}

void	print_history(t_hist *history)
{
	int	k;
	int	counter;

	k = 0;
	counter = history->counter;
	ft_putstr("history:\n");
	while (k < counter)
	{
		ft_putstr(history->arr[k]->name);
		ft_putstr(", ");
		k++;
	}
	ft_putstr("\n");
}
