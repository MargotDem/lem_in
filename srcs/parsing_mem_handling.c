#include "parsing.h"

void	lets_free_all(t_data **data)
{
	// marg : if data isnt modified in here we can just pass *data and not **data
	int i;

	i = 0;

	while ( i < (*data)->size_lst)
	{
		if ((*data)->hashtab[i] != NULL)
		{
			while ((*data)->hashtab[i] != NULL)
			{
				ft_strdel(&(*data)->hashtab[i]->room_name);
				free((*data)->hashtab[i]->links);
				(*data)->hashtab[i] = (*data)->hashtab[i]->h_next;
			}
		}
		free((*data)->hashtab[i]);
		i++;
	}
	// free(rooms)
	free((*data)->hashtab);
	free((*data)->start_room);
	// marg what about (*data)->exit_room
	(*data)->start_room =  NULL;

	// i = 0;
	// while (i < (*data)->size_lst)
	// {
	// 	free((*data)->hashtab[i]);
	// 	i++;
	// }
}

t_room **brealloc(t_room **links,t_room *to, int size_list)
{
	int x;
	t_room **dst;

	x = 0;
	// marg : malloc(sizeof(t_room *) * (size_list + 1));
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

// marg rename to create_link ? and rename element and to into room_1 and room_2 or room and link_room 
void create_links(t_room *element, char *to, t_data **data)
{
	
	int i;
	t_room *temp;
	// marg why not use the hashtable here as well
	temp = search_for(to,data);

	i = 0;
	if(element->links[0] == NULL)
	{
		element->links[0] = temp;
		element->links[1] =  NULL;
		element->size_links = 1;
	}
	else
	{
		element->links = brealloc(element->links, temp, element->size_links);
		element->size_links += 1;
	}
}