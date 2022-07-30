#include "parsing.h"

t_data  *create_data()
{
    t_data *element;

    element = (t_data *)malloc(sizeof(*element));
    // printf("DATA ---> %p\n", element);
    if (!element)
        panic("malloc data");
    return (element);
}

t_room  *new_node(char *line, char letter)
{
    t_room  *new;

    new = (t_room *)malloc(sizeof(*new));
    // printf("new node ---> %p\n", new);
    if (!new)
        panic("malloc new_node");
    new = set_room(line, letter, new);
    return (new);
}

void	create_hashtable(t_data **data)
{
	size_t	i;
	unsigned long	size;

	i = 0;
	size = (*data)->size_list;
	(*data)->hashtab = (t_room **)malloc(sizeof(t_room) * size);
    // printf("HAAASSHHH ---> %p\n", (*data)->hashtab);
	if (!(*data)->hashtab)
		panic("malloc hashtab");
	while (i < size)
	{
		(*data)->hashtab[i] = NULL;
		i++;
	}
}


t_room **brealloc(t_room **links,t_room *to, unsigned long size_list)
{
	size_t x;
	t_room **dst;

	x = 0;
	dst = (t_room **)malloc(sizeof(t_room *) * size_list + sizeof(t_room *));
    // printf("dest --->%p\n", dst);
	if (!dst)
		panic("reallocation memory");
	while ( x < size_list )
	{   
		dst[x] = links[x];
		x++;
	}
	dst[x] = to;
	free(links);
	links = NULL;
	return (dst);
}


char	*cpy_line(char *line, char *map)
{
	char	*temp;
	
	if (!map)
		temp = ft_strdup(line);
	else
		temp = ft_strjoin(map, line);
	if (!temp)
		panic("malloc");
	free(map);
	map = ft_strjoin(temp,"\n");
	ft_strdel(&temp);
	return (map);
}

void    create_links(t_room **room)
{
    (*room)->links = (t_room **)malloc(sizeof(t_room *));
    // printf("LINKS -->%p\n", (*room)->links);
    if (!(*room)->links)
        panic("malloc links");
    (*room)->links[0] = NULL;
}