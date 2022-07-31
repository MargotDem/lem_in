#include "parsing.h"

t_data  *set_data(t_data *node)
{
    node->ants = 0;
    node->help = 0;
    node->visual = 0;
    node->no_map = 0;
    node->end_room_name = NULL;
    node->start_room_name = NULL;
    node->hashtable_created = FALSE;
    node->section_links = DIACTIVATE;
    node->section_rooms = DIACTIVATE;
    node->map = NULL;
    return (node);
}

t_room  *set_room(char *line, char letter, t_room *room)
{
    room->name = save_name(line);
    room->start = FALSE;
    room->end = FALSE;
    room->abscisse = save_abscisse(line);
    room->ordonne = save_ordonne(line);
    room->next = NULL;
    room->hash_next = NULL;
    room->links = NULL;
    if (letter =='s')
        room->start = TRUE;
    else if (letter == 'e')
        room->end = TRUE;
    return (room);
}