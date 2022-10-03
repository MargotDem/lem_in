/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:27:13 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/03 14:27:14 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_vect(t_vector **vector, size_t size)
{
	t_vector	*vect;

	vect = (t_vector *)handle_null(malloc(sizeof(t_vector)));
	vect->size = size;
	vect->counter = 0;
	vect->arr = (void **)handle_null(malloc(sizeof(void *) * size));
	ft_bzero((void *)(vect->arr), size);
	*vector = vect;
}
