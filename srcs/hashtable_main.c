/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:48:41 by briffard          #+#    #+#             */
/*   Updated: 2022/10/07 10:12:47 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

unsigned long	hashing(char *str, unsigned int size)
{
	size_t			i;
	unsigned long	h_index;

	h_index = 0;
	i = 0;
	while (str[i] != '\0')
	{
		h_index += str[i];
		i++;
	}
	return (h_index % size);
}

t_room	*search_for(char *name, t_data *data)
{
	unsigned long	index;
	t_room			*temp;

	index = hashing(name, data->size_list);
	temp = data->hashtab[index];
	while (ft_strcmp(name, temp->name) != 0 && temp != NULL)
		temp = temp->hash_next;
	return (temp);
}

t_room	*insert_room(t_data **data, t_room *li, int index)
{
	t_room	*temp;
	t_room	*tempo;
	t_room	*new;

	new = cpy_room(li);
	if (!new)
		exit_parsing(NULL, li, *data);
	tempo = NULL;
	temp = (*data)->hashtab[index];
	if (temp == NULL)
		return (new);
	else
	{
		tempo = temp;
		while (temp->hash_next != NULL)
			temp = temp->hash_next;
		temp->hash_next = new;
		new->hash_next = NULL;
	}
	return (tempo);
}

void	fill_up_hashtable(t_data **data, t_room *li)
{
	unsigned int	hash_index;
	unsigned long	size;
	t_room			*temp;

	size = (*data)->size_list;
	temp = li;
	hash_index = 0;
	while (temp != NULL)
	{
		hash_index = hashing(temp->name, size);
		(*data)->hashtab[hash_index] = insert_room(data, temp, hash_index);
		temp = temp->next;
	}
}

void	hashtable_main(t_data **data, t_room *li)
{
	(*data)->hashtable_created = TRUE;
	if (!create_hashtable(data))
		exit_parsing(NULL, li, *data);
	fill_up_hashtable(data, li);
	while (li != NULL)
		li = clean_list(li);
}
