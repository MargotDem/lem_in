 #include "parsing.h"


static void     mapreader(int fd, t_room **li, t_data **data);
static void     set_data(t_data *data);

/*Set value in struc data to 0*/
static void     set_data(t_data *data)
{
    data->room_part = 0;
    data->connexion_part = 0;
    data->ants = 0;
    data->size_lst = 0;
    data->hash = 0;
}

/*Verifie si line est un commentaire selon les criteres*/
int      is_comment(char *line)
{
    if (line[0] == '#' && line[1] != '#')
        return (1);
    return (0);
}

int      line_id(char *line, t_data *data)
{
    if (is_room(line, data->connexion_part))
        return (0);
    else if (is_connexion(line, data->room_part))
        return (1);
    else if(is_command(line))
        return (2);
    else 
        return(3);
}

static void data_allocation(t_data **data)
{
    (*data) = (t_data *)malloc(sizeof(**data));
    if (!(*data))
        err_handling("malloc");
    set_data(*data);
}

static void    mapreader(int fd, t_room **rooms, t_data **data)
{
    char *line;
    int     id;

    id = 0;
    line = NULL;
    data_allocation(data);
    (*data)->ants = get_ants(*data, line);
    while (get_next_line(fd, &line) && id >= 0 && (*data)->ants > 0)
    {
        if (is_comment(line))
        {
            ft_strdel(&line);
            if (get_next_line(0, &line) == 0)
                break;
        }
        id = line_id(line, *data);
        g_line_dispatch[id](rooms, line, data);
        ft_strdel(&line);
    }
}


int main(void)
{
    t_room  *rooms;
    t_data  *data;

    rooms = NULL;
    data = NULL;
    mapreader(0, &rooms, &data);
    check_data(data);
	test_solver(search_for(data->start_room, data));
    //solve(search_for(data->start_room, data), data);
    free_all(&data);
    free(rooms);
    free(data);
    return (0);
}