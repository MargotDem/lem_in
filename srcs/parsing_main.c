#include "parsing.h"

// marg why
static void     mapreader(int fd, t_room **li, t_data **data);
static int      is_a_comment(char *line);
static void     set_data(t_data **data);

/*Set value in struc data to 0*/
// marg rename init_data ? and no need to pass **data only *data
static void     set_data(t_data **data)
{
    (*data)->room_part = 0;
    (*data)->connexion_part = 0;
    (*data)->ants = 0;
    (*data)->size_lst = 0;
    (*data)->hash = 0;
}

/*Verifie si line est un commentaire selon les criteres*/
static int      is_a_comment(char *line)
{
    if (line[0] == '#' && line[1] != '#')
        return (1);
    return (0);
}

// static int      (*line_id(char *line, t_data *data))(t_room **li, char *line)
int      line_id(char *line, t_data **data/*, t_room **li*/)
{
    if (is_a_room(line, (*data)->connexion_part))
        return (0);
    else if (is_a_connexion(line, (*data)->room_part))
        return (1);
    else if(is_a_command(line))
        return (2);
    return (3);
}

// marg can we rename li to rooms
static void    mapreader(int fd, t_room **li, t_data **data)
{
    char *line;
    int     id;

    id = 0;
    line = NULL;
	// marg sizeof t_data ?
    (*data) = (t_data *)malloc(sizeof(**data));
    if (!(*data))
        err_handling("malloc");
    set_data(data);
    (*data)->ants = get_ants();
	// marg why check data if ants == 0, shouldnt we just exit or display error ?
    if ((*data)->ants == 0)//pas la bonne idee !!!
        check_data(data);
    while (get_next_line(fd, &line))
    {
        if (is_a_comment(line))
        {
            ft_strdel(&line);
            get_next_line(0, &line);
        }
        id = line_id(line, data/*, li*/);
        if (id == -1)
        {
            ft_strdel(&line);
            break;
        }
		// marg if the ptr to data is never changed anywhere (is it?) then we dont need to pass t_data **data
        line_dispatch[id](li, line, data);
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
    if (check_data(&data))
    {
        g_head = search_for(data->start_room, &data);
        //envoyer vers le solveur
		solve(g_head, data);
    }
    // printf("There is %d ants\n", data->ants);
    // print_lst(rooms);
    // printf("Size list: %d\n", data->size_lst);
    // print_connexion(&data);

    lets_free_all(&data);
    free(rooms);
    free(data);

    return (0);
}
