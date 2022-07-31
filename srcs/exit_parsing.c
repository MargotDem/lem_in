#include "parsing.h"

unsigned short data_is_ok(t_data *data)
{
    if (data->ants == 0)
        return (FALSE);
    if (!data->end_room_name || !data->start_room_name)
        return (FALSE);
    return (TRUE);
}

void    exit_parsing(t_room *rooms, t_data *data)
{
    if (rooms)
    {
        while(rooms != NULL)
		rooms = my_clean(rooms);
    }
    if (data_is_ok(data))
    {
        print_line(data->map, data->size_map);
        printf("go_to_solver");
        data = data_cleaner(data);
        exit(EXIT_SUCCESS);
    }
    printf("error\n");  
    data = data_cleaner(data);
    exit(EXIT_FAILURE);
}