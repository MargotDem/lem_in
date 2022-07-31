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
    if (rooms && data->hashtable_created == 0)
        while(rooms != NULL)
		    rooms = my_clean(rooms);
    if (data_is_ok(data))
    {
        write(1, data->map, data->index_line);
        printf("go_to_solver");
        data = data_cleaner(data);
        system("leaks lem-in");
        exit(EXIT_SUCCESS);
    }
    ft_putstr("error\n"); 
    data = data_cleaner(data);
    system("leaks lem-in");
    exit(EXIT_FAILURE);
}