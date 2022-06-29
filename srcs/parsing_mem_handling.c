#include "parsing.h"

t_room **brealloc(t_room **links,t_room *to)
{
    int i;
    int x;
    t_room **dst;

    i = 0;
    x = 0;
    printf("TEST@\n");
    while((*links)->links[i] != NULL) // cree un segfault
        i++;
    dst = malloc(sizeof(t_room) * i + 1);
    printf("t_room ** dst created\n");
    if (!dst)
        mem_error("Creation dst", "parsing_handling.c", 13);
    while ( x < i)
    {   
        dst[x] = (*links)->links[x];
        free((*links)->links[x]);
        x++;
    }
    dst[x] =  to;
    free((*links)->links[x]);
    free((*links));
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

// (*data)->hashtab = malloc(sizeof(t_room) * ((*data)->size_lst));
void create_links(t_room *element,char *to, t_data **data)
{
    
    int i;
    t_room *temp;
    temp = search_for(to,data);
    i = 0;
    if(element->links == NULL)
    {
        element->links = malloc(sizeof(t_room) * 1);
       	if(!element->links)
		    mem_error("Creation links","parsing_handling.c", 52);
        element->links[0] = temp;
		element->links[1] =  NULL;
    }
    else
        element->links = brealloc(element->links, temp);
}