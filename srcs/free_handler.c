/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:54 by briffard          #+#    #+#             */
/*   Updated: 2022/08/01 11:45:05 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_room	*my_clean(t_room *list)
{
	t_room	*temp;

	if (list->next == NULL)
	{
		if (list->name)
			ft_strdel(&list->name);
		if (list->links)
			free(list->links);
		list->next = NULL;
		if (list)
			free(list);
		return (NULL);
	}
	temp = list->next;
	if (list->name)
		free(list->name);
	if (list->links)
		free(list->links);
	list->next = NULL;
	if (list)
	{
		free(list);
		list = NULL;
	}
	return (temp);
}

t_room	*my_clean_data(t_room *list)
{
	t_room	*temp;

	if (list->hash_next == NULL)
	{
		if (list->name)
			free(list->name);
		if (list->links)
			free(list->links);
		if (list)
			free(list);
		return (NULL);
	}
	temp = list->hash_next;
	if (list->name)
		free(list->name);
	if (list->links)
		free(list->links);
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
	while (i < data->size_list)
	{
		temp = data->hashtab[i];
		if (temp)
		{
			while (temp != NULL)
				temp = my_clean_data(temp);
		}
		i++;
	}
	if (data->hashtable_created == TRUE)
		free(data->hashtab);
	return (free(data), NULL);
}

void	clean2str(char *s1, char *s2)
{
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
}