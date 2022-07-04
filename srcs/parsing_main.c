#include "parsing.h"


static void     mapreader(int fd, t_room **li, t_data **data);
static int      is_comment(char *line);
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
static int      is_comment(char *line)
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
    check_data(data);
    return (-1);
}

// marg can we rename li to rooms
static void    mapreader(int fd, t_room **rooms, t_data **data)
{
    char *line;
    int     id;

    id = 0;
    line = NULL;
	// marg sizeof t_data ?
    //bapt: if i do malloc(sizeof(*data) -> SEGFAULT or malloc(sizeof(data) -> SEGFAULT
    (*data) = (t_data *)malloc(sizeof(**data));
    if (!(*data))
        err_handling("malloc");
    set_data(*data);
    (*data)->ants = get_ants(*data);
    while (get_next_line(fd, &line))
    {
        if (is_comment(line))
        {
            ft_strdel(&line);
            get_next_line(0, &line);
        }
        id = line_id(line, *data);
        if (id == -1)
        {
            ft_strdel(&line);
            break;
        }
		// marg if the ptr to data is never changed anywhere (is it?) then we dont need to pass t_data **data
        // BAPT: data is changed in is _room or is connexion. the hashtable is created is connexion
        line_dispatch[id](rooms, line, data);
        ft_strdel(&line);
    }
}


int main(void)
{
    t_room  *rooms;
    t_room  *g_head;
    t_data  *data;

    rooms = NULL;
    data = NULL;
	g_head = NULL;

    mapreader(0, &rooms, &data);
    //On verifie si on a assez de donnee pour 
    if (check_data(data))
    {
        g_head = search_for(data->start_room, data);
        //envoyer vers le solveur
    }

	printf("here is the start room: %s\n", g_head->room_name);
    free_all(&data);
    free(rooms);
    free(data);
    return (0);

}

