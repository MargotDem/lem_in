#include "parsing.h"

void	free_all(t_data **data)
{
	// marg : if data isnt modified in here we can just pass *data and not **data
	// bapt: I was thinking that because we are freeing we will need  **data
	int i;

	i = 0;

	while ( i < (*data)->size_lst)
	{
		if ((*data)->hashtab[i] != NULL)
		{
			while ((*data)->hashtab[i] != NULL)
			{
				ft_strdel(&(*data)->hashtab[i]->name);
				free((*data)->hashtab[i]->links);
				(*data)->hashtab[i] = (*data)->hashtab[i]->h_next;
			}
		}
		free((*data)->hashtab[i]);
		i++;
	}

	free((*data)->hashtab);
	free((*data)->start_room);
	free((*data)->exit_room);
	(*data)->exit_room = NULL;
	(*data)->start_room =  NULL;
}

t_room **brealloc(t_room **links,t_room *to, int size_list)
{
	int x;
	t_room **dst;

	x = 0;
	// marg : malloc(sizeof(t_room *) * (size_list + 1));
	// bapt : + 1 is for the extra I need to make it dynamic
	dst = (t_room **)malloc(sizeof(t_room *) * size_list + sizeof(t_room *));
	if (!dst)
		err_handling("malloc");
	while ( x < size_list )
	{   
		dst[x] = links[x];
		x++;
	}
	dst[x] =  to;
	return (dst);
}

void    *ft_cleanstr(char **s, size_t i)
{
	size_t  j;

	j = 0;
	while (j < i)
	{
		free(s[j]);
		j++;
	}
	free(s);
	return (NULL);
}

void create_link(t_room *room_1, t_room *room_2)
{
	
	if(room_1->links[0] == NULL)
	{
		room_1->links[0] = room_2;
		room_1->links[1] =  NULL;
		room_1->nb_links= 1;
	}
	else
	{
		room_1->links = brealloc(room_1->links, room_2, room_1->nb_links);
		room_1->nb_links += 1;
	}
}

void	insert_links(t_room *room1, t_room *room2)
{
	create_link(room1, room2);
	create_link(room2, room1);
}