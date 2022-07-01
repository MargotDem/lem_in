#include "parsing.h"

void	lets_free_all(t_data **data)
{
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
	dst = (t_room **)malloc(sizeof(t_room *) * size_list + sizeof(t_room *));
	if (!dst)
		err_handling("mallloc");
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

void create_links(t_room *element,char *to, t_data **data)
{
	
	int i;
	t_room *temp;
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