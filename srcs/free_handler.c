/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:54 by briffard          #+#    #+#             */
/*   Updated: 2022/10/05 13:43:25 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	inside_clean(t_room *element)
{
	if (element->name)
		ft_strdel(&element->name);
	if (element->links)
		free(element->links);
}

t_room	*clean_list(t_room *list)
{
	t_room	*temp;

	temp = NULL;
	inside_clean(list);
	if (list->next != NULL)
		temp = list->next;
	if (list)
	{	
		free(list);
		list = NULL;
	}
	return (temp);
}

t_room	*clean_hash(t_room *list)
{
	t_room	*temp;

	temp = NULL;
	inside_clean(list);
	if (list->hash_next != NULL)
		temp = list->hash_next;
	if (list)
	{	
		free(list);
		list = NULL;
	}
	return (temp);
}

t_data	*data_cleaner(t_data *data)
{
	size_t	i;
	t_room	*temp;

	i = 0;
	if (data->start_room_name)
		ft_strdel(&data->start_room_name);
	if (data->end_room_name)
		ft_strdel(&data->end_room_name);
	if (data->map)
		ft_strdel(&data->map);
	if (data->hashtab)
	{
		while (i < data->size_list)
		{
			temp = data->hashtab[i];
			if (temp)
				while (temp != NULL)
					temp = clean_hash(temp);
			i++;
		}
	}
	if (data->hashtable_created == TRUE)
		free(data->hashtab);
	return (free(data), NULL);
}

void	clean2str(char *s1, char *s2, char letter)
{
	if (letter == 'n')
	{
		if (s1)
			ft_strdel(&s1);
		if (s2)
			ft_strdel(&s2);
	}
	else if (letter == 's')
	{
		if (s1)
			ft_strdel(&s1);
	}
	else if (letter == 'e')
	{
		if (s2)
			ft_strdel(&s2);
	}
}
