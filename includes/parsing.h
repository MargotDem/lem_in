#ifndef PARSING_H
# define PARSING_H

/*INCLUDES*/
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

/*STRUCTURE*/
typedef struct s_room{
	char *room_name;
	int line;
	int row;
	int room_start;
	int room_end;
	int size_links;

	/*POINTER LINK LIST*/
	struct s_room *next;
	struct s_room *h_next;
	struct s_room **links;
}	t_room;

typedef struct s_data {

	int room_part;
	int connexion_part;
	int size_lst;
	int hash;
	int ants; // ULL pour plus de possibilite
	struct s_room **hashtab; //HASH TABLE FOR ROOMS
	char *start_room;
}       t_data;

/*ARRAY POINTER FUNCTION*/
void    get_room(t_room **li, char *line, t_data **data);
void    get_connexion(t_room **li, char *line, t_data **data);
void    get_command(t_room **li, char *line, t_data **data);

typedef void (*t_line_dispatcher)(t_room **li, char *line, t_data **data);
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

/*PARSING_CONNEXION_HANDLING*/
int		existing_room(char *conexion, t_data **hashtab);
void 	add_links(t_data **data, char *from, char *to);
t_room 	*search_for(char *connexion, t_data **data);
int		index_of_chr(char *str, char c);
void	print_connexion(t_data **data);


/*PARSING_MAIN*/
int      line_id(char *line, t_data **data/*, t_room **li*/);

/*PARSING_COMMAND*/
int     is_a_command(char *line);

/*HASHTABLE_MAIN*/
void				hashtable_main(t_data **data, t_room *li);
unsigned long		hashing(char *str, unsigned int size);

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
void 	create_links(t_room *element,char *to, t_data **data);
void	lets_free_all(t_data **data);

#endif