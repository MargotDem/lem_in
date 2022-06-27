#include "parsing.h"

/*
	hashs est un tableau de structure room au max size
	chaque struct est positionnee a un index defnit par la fonction de hashage
	si un un struct est deja presente sur l index
	il faut l ajouter a la suite la structure deja presente 
	mais que faire des index non utiliser
	*/

// void	print_hashtab(t_data **data)
// {
// 	int i = 0;
// 	printf("HASHTABLE--------------------------\n");
// 	while (i < (*data)->size_lst + 2)
// 	{
// 		printf("INDEX: %d\n", i);
// 		printf("room name: %s\n", (*data)->hashtab[i].room_name);
//         printf("Line: %d && Row: %d\n", (*data)->hashtab[i].line, (*data)->hashtab[i].row);
//         if ((*data)->hashtab[i].room_end)
//             printf("This is the ending room\n");
//         else if ((*data)->hashtab[i].room_start)
//             printf("This is the starting room\n");
//         else
//             printf("This is the normal room\n");

//         printf("--------------------------------\n");
// 		i++;
// 	}
// }


void	create_hashtable(t_data **data)
{
	int	i;

	i = 0;
	(*data)->hashtab = malloc(sizeof(t_room) * ((*data)->size_lst * 2));
	if(!(*data)->hashtab)
		mem_error("Creation hashtable","hastable_main.c", 38);
	while (i < ((*data)->size_lst * 2))
	{
		(*data)->hashtab[i] = NULL;
		i++;
	}
}

unsigned int		hashing(char *str, int size)
{
	int	i;
	unsigned int h_index;

	i = 0;
	h_index = 0;
	while (str[i] != '\0')
	{
		h_index = str[i] + 31 * h_index;
		i++;
	}

	return (h_index % size);
}

t_room	*insert_room(t_data **data, t_room *li, int index)
{
	t_room *temp;

	temp = (*data)->hashtab[index];
	if ((*data)->hashtab[index] == NULL)
	{
		li-> h_next = NULL;
		return (li);
	}
	else
	{
		while (temp->h_next != NULL)
			temp= temp->h_next;
		temp->h_next = li;
		li->h_next = NULL;
	}
	return (li);
}

void	fill_up_hashtable(t_data **data, t_room **li)
{
	unsigned int	hash_index;
	t_room	*temp;

	temp = (*li);
	hash_index = 0;
	while (temp != NULL)
	{
		hash_index = hashing(temp->room_name, ((*data)->size_lst + 1) );
		printf("room_name: %s || size: %d  || h_index -> %d\n",temp->room_name,((*data)->size_lst + 1) , hash_index);
		(*data)->hashtab[hash_index]= insert_room(data, temp, hash_index);
		temp = temp->next;
	}
}


void	hashtable_main(t_data **data, t_room **li)
{
	create_hashtable(data);
	fill_up_hashtable(data, li);
	// print_hashtab(data);
}