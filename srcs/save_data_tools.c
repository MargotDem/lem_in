#include "parsing.h"

void create_link(t_room *room_1, t_room *room_2)
{
	
	if(room_1->links[0] == NULL)
	{
		room_1->links[0] = room_2;
		room_1->total_links = 1;
	}
	else
	{
		room_1->links = brealloc(room_1->links, room_2, room_1->total_links);
		room_1->total_links += 1;
	}
}

void	insert_links(t_room *from, t_room *to)
{
	create_link(from, to);
	create_link(to, from);
}