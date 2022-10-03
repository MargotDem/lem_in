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
	ft_bzero((void *)(vect->arr), sizeof(void *) * size);
	*vector = vect;
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

//

void	init_vect_str(t_vector_string **vector, size_t size)
{
	t_vector_string	*vect;

	vect = (t_vector_string *)handle_null(malloc(sizeof(t_vector_string)));
	vect->size = size;
	vect->counter = 0;
	vect->str = (char *)handle_null(malloc(sizeof(char) * size));
	ft_bzero((void *)(vect->str), sizeof(char) * size);
	*vector = vect;
}

void	push_to_vect_str(t_vector_string *vector, char el)
{
	char	*tmp;
	int		i;
	int		counter;
	int		size;

	counter = vector->counter;
	size = vector->size;
	if (counter && counter % size == 0)
	{
		tmp = (char *)handle_null(\
			malloc(sizeof(char) * (counter + size)));
		i = 0;
		while (i < counter)
		{
			tmp[i] = vector->str[i];
			i++;
		}
		i = 0;
		free(vector->str);
		vector->str = tmp;
	}
	vector->str[counter] = el;
	vector->counter++;
}

void	free_vect_str(t_vector_string **vector)
{
	if (*vector)
	{
		free((*vector)->str);
		free(*vector);
		*vector = NULL;
	}
}
