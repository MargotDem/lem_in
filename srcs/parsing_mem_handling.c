#include "parsing.h"

t_room **brealloc(t_room **links,t_room *to, int size_list)
{
	int x;
	t_room **dst;

	x = 0;
	printf("VALEUR SL = %d\n", size_list);
	dst = (t_room **)malloc(sizeof(t_room *) * size_list + sizeof(t_room *));
	// printf("t_room ** dst created\n");
	if (!dst)
		mem_error("Creation dst fail", "parsing_handling.c", 13);
	while ( x < size_list )
	{   
		dst[x] = links[x];
		x++;
	}
	printf("index insert new pointer = %d\n", x);
	dst[x] =  to;
	dst[size_list + 1] =  NULL;
	printf("Element added -> %s\n", dst[x]->room_name);
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
		printf("LinkK between %s et %s\n", element->room_name, temp->room_name);
		element->links = brealloc(element->links, temp, element->size_links);
		element->size_links += 1;
	}
	// printf("ELEMENT->links[1]-> %s\n", element->links[1]->room_name);
}