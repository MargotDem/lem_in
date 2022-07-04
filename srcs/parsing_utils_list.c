#include "parsing.h"

static t_room   *set_pointer(t_room *li, t_room *element);
static t_room   *set_null_pointer(t_room *element);


void    print_lst(t_room *li)
{
    t_room *temp;

    temp = li;
    while (li != NULL)
    {
        printf("room name: %s\n", li->room_name);
        printf("Line: %d && Row: %d\n", li->line, li->row);
        if (li->room_end)
            printf("This is the ending room\n");
        else if (li->room_start)
            printf("This is the starting room\n");
        else
            printf("This is the normal room\n");

        printf("--------------------------------\n");
        li =li->next;
    }
}

static t_room   *set_pointer(t_room *li, t_room *element)
{
    if (li->next ==  NULL)
        li->next = element;
    else
    {
        element->next = li->next;
        li->next = element;
    }
    return (li);
}

static t_room   *set_null_pointer(t_room *element)
{
    element->next =  NULL;
    element->h_next = NULL;
    element->links = (t_room **)malloc(sizeof(t_room *) * 2);
    if (!element->links)
        err_handling("malloc");
    element->links[0] =  NULL;
    element->links[1] =  NULL;
    return (element);
}


t_room  *new_node(char *line, char c)
{
    t_room  *node;
    
    node = malloc(sizeof(*node));
    if (!node)
        err_handling("malloc");
    node->room_name = extract_name(line);
    node->line = extract_line(line);
    node->row = extract_row(line);
    node->size_links = 0;
    node = set_startorend(node, c);
    node = set_null_pointer(node);
    printf("Creation de %s avec les valeurs line = %d && row = %d\n", node->room_name, node->line, node->row);
    return (node);
}

t_room  *push_t_room(t_room *room, t_room *element)
{
    t_room  *head;

    if (room == NULL)
        return (element);
    head = room;
    if (ft_strcmp(room->room_name, element->room_name) > 0)
    {
        element->next = room;
        room = element;
        return (room);
    }
    while (room->next !=  NULL)
    {
        if (ft_strcmp(room->room_name, element->room_name) < 0 &&\
        ft_strcmp(element->room_name, room->next->room_name) < 0)
            break;
        room = room->next;
    }
    room = set_pointer(room, element);
    return (head);
}
