/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:27:13 by mde-maul          #+#    #+#             */
/*   Updated: 2022/10/10 12:44:42 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	init_vect(t_vector **vector, size_t size)
{
	t_vector	*vect;

	vect = (t_vector *)(malloc(sizeof(t_vector)));
	if (!vect)
		return (ERROR);
	vect->size = size;
	vect->counter = 0;
	vect->arr = (void **)(malloc(sizeof(void *) * size));
	if (!vect->arr)
		return (ERROR);
	ft_bzero((void *)(vect->arr), sizeof(void *) * size);
	*vector = vect;
	return (OK);
}

void	push_to_vect(t_vector *vector, void *el)
{
	void	**tmp;
	int		i;
	int		counter;
	int		size;

	counter = vector->counter;
	size = vector->size;
	if (counter && counter % size == 0)
	{
		tmp = (void **)handle_null(\
			malloc(sizeof(void *) * (counter + size)));
		i = 0;
		while (i < counter)
		{
			tmp[i] = vector->arr[i];
			i++;
		}
		i = 0;
		free(vector->arr);
		vector->arr = tmp;
	}
	vector->arr[counter] = el;
	vector->counter++;
}

void	free_vect(t_vector **vector)
{
	if (*vector)
	{
		free((*vector)->arr);
		free(*vector);
		*vector = NULL;
	}
}

void	concat_vects(t_vector *src, t_vector **dst)
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
		init_vect(dst, size);
	while (i < counter)
	{
		push_to_vect(*dst, src->arr[i]);
		i++;
	}
}
