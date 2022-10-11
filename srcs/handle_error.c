/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:53:55 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/07 13:53:58 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	handle_error(void)
{
	write(2, "ERROR\n", 6);
}

void	*handle_null(void *param)
{
	if (!param)
	{
		handle_error();
		exit(1);
	}
	return (param);
}

void	exit_solver(t_vector *vector, t_data *data)
{
	if (vector)
		free_vect(&vector);
	if (data)
		data = data_cleaner(data);
	system("leaks lem-in > exit_s_leaks.txt");
	system("leaks lem-in > exit_leaks.txt");
	exit(EXIT_FAILURE);
}
