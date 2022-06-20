#ifndef PARSING_H
# define PARSING_H

/*INCLUDES*/
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

/*STRUCTURE*/
typedef struct s_room{
	char *room_name;
    int line;
    int row;
	/*POINTER LINK LIST*/
	struct s_room *next;
    /*POOINTER TREE*/
    struct s_room *treehead;
    struct s_room *left;
    struct s_room *rigth;
    struct s_room *parent;
}	t_room;

typedef struct s_data {

    int room_part;
    int connexion_part;
    int room_start;
    int room_end;
    int size_lst;
    int ants; // ULL pour plus de possibilite
}       t_data;

/*ARRAY POINTER FUNCTION*/
void    get_room(t_room **li, char *line);
void    get_connexion(t_room **li, char *line);
// void (*line_dispatch[1])(t_room **li, char *line) = {get_room};
// t_room *get_connexion(t_room *li, t_data *data, char *line);
// t_room *get_out(t_room *li, t_data *data, char *line);
// t_room *get_command(t_room *li, t_data *data, char *line);

typedef void (*t_line_dispatcher)(t_room **li, char *line);
static t_line_dispatcher line_dispatch[2] = {
    get_room,
    get_connexion,
};

/*PROTOTYPE*/
/*PARSING_ANTS*/
int get_ants();

/*PARSING_ROOMS*/
int is_a_room(char *line, int  active_connextion);

/*PARSING_CONNEXION*/
int is_a_connexion(char *line, int active_room);

/*UTILS*/
int	countwords(char const *s, char c);
char	*extract_name(char *line);
int	extract_row(char *line);
int	extract_line(char *line);
int	check_word(char **arr);

/*UTILS_2*/
int skip_word(char *line);
int skip_space(char *line);

/*UTILS_LIST*/
t_room  *new_node(char *line);
t_room  *push(t_room *li, t_room *element);
void    print_lst(t_room *li);

/*ERROR*/
void    mem_error(char *message, char *where, int line);

/*MEM_HANDLING*/
void    *ft_cleanstr(char **s, size_t i);

#endif