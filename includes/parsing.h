#ifndef PARSING_H
# define PARSING_H

/*STRUCTURE*/
typedef struct s_room{
	char *room_name;
	
	/*POINTER LINK LIST*/
	struct s_room *next;
}	t_room;

typedef struct s_data {

    int room_part;
    int connexion_part;
    int room_start;
    int room_end;

}t_data;

/*ARRAY POINTER FUNCTION*/
void get_comment(t_room *li, t_room *data);
void get_room(t_room *li, t_room *data);
void get_connexion(t_room *li, t_room *data);
void get_out(t_room *li, t_room *data);
void get_command(t_room *li, t_room *data);

typedef void    (*dispatcher)(t_room *li, t_room *data);
static const    dispatcher line_dispatch[5] = {
    get_comment,
    get_room,
    get_connexion,
    get_command,
    get_out,
};

#endif