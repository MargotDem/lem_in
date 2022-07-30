#include "parsing.h"

void	create_hashtable(t_data **data)
{
	int	i;
	int	size;

	i = 0;
	size = (*data)->size_lst;
	(*data)->hashtab = malloc(sizeof(t_room) * size);
	if (!(*data)->hashtab)
		err_handling("malloc");
	while (i < size)
	{
		(*data)->hashtab[i] = NULL;
		i++;
	}
}

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

t_room	*insert_room(t_data **data, t_room *li, int index)
{
	t_room	*temp;
	t_room	*tempo;

	tempo = NULL;
	temp = (*data)->hashtab[index];
	if ((*data)->hashtab[index] == NULL)
	{
		temp = li;
		return (temp);
	}
	else
	{
		tempo = temp;
		while (temp->h_next != NULL)
			temp = temp->h_next;
		temp->h_next = li;
		li->h_next = NULL;
	}
	return (tempo);
}

void	print_hashtab(t_data **data)
{
	int		i;
	t_room	*temp;

	i = 0;
	temp = NULL;
	while (i < (*data)->size_lst)
	{
		temp = (*data)->hashtab[i];
		if (temp != NULL)
		{
			while (temp != NULL)
			{
				printf("VALEUR -> %s || INDEX -> %d\n", temp->name, i);
				temp = temp->h_next;
			}
		}
		i++;
	}
}

void	fill_up_hashtable(t_data **data, t_room *li)
{
	unsigned int	hash_index;
	t_room			*temp;

	temp = li;
	hash_index = 0;
	while (temp != NULL)
	{
		hash_index = hashing(temp->name, (*data)->size_lst);
		(*data)->hashtab[hash_index] = insert_room(data, temp, hash_index);
		temp = temp->next;
	}
}

void	hashtable_main(t_data **data, t_room *li)
{
	(*data)->hash = 1;
	create_hashtable(data);
	fill_up_hashtable(data, li);
	// print_hashtab(data);
}
