#include "parsing.h"

static void     mapreader(int fd, t_room **li, t_data **data);
static int      is_a_comment(char *line);
static void     set_data(t_data **data);

/*Set value in struc data to 0*/
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
int      line_id(char *line, t_data **data, t_room **li)
{
    if (is_a_room(line, (*data)->connexion_part))
    {
        (*data)->room_part = 1;
        (*data)->size_lst += 1; 
        return (0);
    }
    else if (is_a_connexion(line, (*data)->room_part))
    {
        if((*data)->hash == 0)
        {
            (*data)->hash = 1;
            hashtable_main(data, li);
        }
        (*data)->connexion_part = 1;
        return (1);
    }
    else if(is_a_command(line))
        return (2);
    return (3);
}

static void    mapreader(int fd, t_room **li, t_data **data)
{
    char *line;

    (*data) = (t_data *)malloc(sizeof(**data));
    set_data(data);
    (*data)->ants = get_ants();
    while (get_next_line(fd, &line))
    {
        if (is_a_comment(line))
            get_next_line(0, &line);
        line_dispatch[line_id(line, data, li)](li, line);
    }
    free(line); // remplacer par ft_cleanstr ou strdel
    line = NULL;
}


int main(void)
{
    t_room  *rooms;
    t_data  *data;

    rooms = NULL;
    data = NULL;

    mapreader(0, &rooms, &data);
    printf("There is %d ants\n", data->ants);
    print_lst(rooms);
    printf("Size list: %d\n", data->size_lst);
    return (0);

}

