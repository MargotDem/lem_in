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
    int room_start;
    int room_end;
	/*POINTER LINK LIST*/
	struct s_room *next;
    struct s_room *h_next;
}	t_room;

typedef struct s_data {

    int room_part;
    int connexion_part;
    int size_lst;
    int hash;
    int ants; // ULL pour plus de possibilite
    struct s_room **hashtab;
}       t_data;

/*ARRAY POINTER FUNCTION*/
void    get_room(t_room **li, char *line);
void    get_connexion(t_room **li, char *line);
void    get_command(t_room **li, char *line);

typedef void (*t_line_dispatcher)(t_room **li, char *line);
static t_line_dispatcher line_dispatch[3] = {
    get_room,
    get_connexion,
    get_command,
};

/*PROTOTYPE*/
/*PARSING_ANTS*/
int get_ants();

/*PARSING_ROOMS*/
int is_a_room(char *line, int  active_connextion);

/*PARSING_CONNEXION*/
int is_a_connexion(char *line, int active_room);

/*PARSING_MAIN*/
int      line_id(char *line, t_data **data, t_room **li);

/*PARSING_COMMAND*/
int     is_a_command(char *line);

/*HASHTABLE_MAIN*/
void	hashtable_main(t_data **data, t_room **li);

/*BINARY TREE*/
t_room *createtree(t_room **li, int size_lst);

/*UTILS*/
int	    countwords(char const *s, char c);
char    *extract_name(char *line);
int	    extract_row(char *line);
int	    extract_line(char *line);
int	    check_word(char **arr);

/*UTILS_2*/
int     skip_word(char *line);
int     skip_space(char *line);
t_room  *set_startorend(t_room *element, char c);

/*UTILS_LIST*/
t_room  *new_node(char *line, char c);
t_room  *push(t_room *li, t_room *element);
void    print_lst(t_room *li);

/*ERROR*/
void    mem_error(char *message, char *where, int line);

/*MEM_HANDLING*/
void    *ft_cleanstr(char **s, size_t i);

#endif