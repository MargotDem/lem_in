#include "parsing.h"

void	create_hashtable(t_data **data)
{
	int	i;

	i = 0;
	(*data)->hashtab = malloc(sizeof(t_room) * ((*data)->size_lst));
	if(!(*data)->hashtab)
		mem_error("Creation hashtable","hastable_main.c", 39);
	while (i < ((*data)->size_lst))
	{
		(*data)->hashtab[i] =  NULL;
		i++;
	}
	printf("Hashtable created\n");
}


unsigned long		hashing(char *str, unsigned int size)
{
	size_t	i;
	unsigned long h_index = 0;
	i = 0;
    while (str[i] != '\0')
    {
		h_index +=  str[i];
		i++;
	}
	return (h_index % size);
}

t_room	*insert_room(t_data **data, t_room *li, int index)
{
	t_room *temp;
	t_room *tempo;
	
	tempo = NULL;
	int i = 0;
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
		{
			temp = temp->h_next;
			printf("%d\n", i++);
		}
		temp->h_next = li;
		li->h_next = NULL;
	}

	return (tempo);
}


void	print_hashtab(t_data **data)
{
	int i = 0;
	t_room *temp = NULL;

	while ( i < (*data)->size_lst)
	{
		temp = (*data)->hashtab[i];
		if (temp != NULL)
		{
			while (temp != NULL)
			{
				printf("VALEUR -> %s || INDEX -> %d\n", temp->room_name, i);
				temp = temp->h_next;
			}
		}
		i++;
	}
}

void	fill_up_hashtable(t_data **data, t_room *li)
{
	unsigned int	hash_index;
	t_room	*temp;

	temp = li;
	hash_index = 0;
	while (temp != NULL)
	{
		hash_index = hashing(temp->room_name, (*data)->size_lst );
		(*data)->hashtab[hash_index] = insert_room(data, temp, hash_index);
		temp = temp->next;
	}
}


void	hashtable_main(t_data **data, t_room *li)
{
	printf("%s================%s========================%s\n", "\x1B[33m", "HASHTABLE PART", "\x1B[0m");
	(*data)->hash = 1;
	create_hashtable(data);
	fill_up_hashtable(data, li);
	// print_hashtab(data);
	printf("%s================   END ========================%s\n", "\x1B[33m", "\x1B[0m");
}