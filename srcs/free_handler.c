#include "parsing.h"

t_room	*my_clean(t_room *list)
{
	t_room *temp;
	if (list->next ==  NULL)
	{
		if(list->name)
			ft_strdel(&list->name);
		if (list->links)
			free(list->links);
		list->next = NULL;
		if(list)
		{
			free(list);
			list = NULL;
		}
		return (NULL);
	}
	temp = list->next;
	if(list->name)
		free(list->name);
	if (list->links)
		free(list->links);
	list->next = NULL;
	if(list)
	{
		free(list);
		list = NULL;
	}
	return (temp);
}

t_room	*my_clean_data(t_room *list)
{
	t_room *temp;

	if (list->hash_next ==  NULL)
	{
		free(list->name);
		free(list->links);
		free(list);
		list = NULL;
		return (NULL);
	}
	temp = list->hash_next;
	free(list->name);
	free(list->links);
	free(list);
	list = NULL;
	return (temp);

}

t_data	*data_cleaner(t_data *data)
{
	ft_strdel(&data->start_room_name);
	ft_strdel(&data->end_room_name);
	ft_strdel(&data->map);

	t_room *temp;
	size_t i = 0;
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
	free(data->hashtab);
	free(data);
	return (NULL);
}

void    clean2str(char *s1, char *s2)
{
	if(s1)
    	ft_strdel(&s1);
	if(s2)
    	ft_strdel(&s2);
}