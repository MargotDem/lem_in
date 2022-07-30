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

t_room *search_for(char *name, t_data *data)
{
	unsigned long index;
	t_room *temp;

	index = hashing(name, data->size_list);
	temp = data->hashtab[index];
	while (ft_strcmp(name, temp->name) != 0 && temp != NULL)
		temp = temp->hash_next;
	return (temp);
}

t_room	*set_copy(t_room *dst, t_room *source)
{
	dst->name = ft_strdup(source->name);
	dst->abscisse = source->abscisse;
	dst->ordonne = source->ordonne;
	dst->end = source->end;
	dst->start = source->start;
	dst->total_links = 0;
	dst->hash_next = NULL;
	dst->next = NULL;
	dst->links = (t_room **)malloc(sizeof(t_room *));
	// printf("LINKS -> %p\n", dst->links);
	if (!dst->links)
		panic("malloc links");
	return (dst);
}

t_room *cpy_room(t_room *room)
{
	t_room *element;

	element = (t_room *)malloc(sizeof(t_room));
	// printf("element -> %p\n", element);
	if (!element)
		panic("malloc cpy_room");
	element = set_copy(element, room);
	return (element);
}


t_room	*insert_room(t_data **data, t_room *li, int index)
{
	t_room	*temp;
	t_room	*tempo;
	t_room	*new;

	new = cpy_room(li);

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
	create_hashtable(data);
	fill_up_hashtable(data, li);
	while(li != NULL)
		li = my_clean(li);
}