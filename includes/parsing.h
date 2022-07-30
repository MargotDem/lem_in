#ifndef PARSING_H
# define PARSING_H

/*INCLUDES*/
# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define ACTIVATE 1
# define DIACTIVATE 0
# define ROOMS 0
# define COMMAND 1
# define LINKS 2
# define COMMENT 3
# define EXIT_PARSING 4

/*STRUCTURE*/
typedef struct s_room
{
	char			*name;
    unsigned short  start;
    unsigned short  end;
    unsigned long   abscisse;
    unsigned long   ordonne;

    struct s_room   *next;
    struct s_room   *hash_next;
    
    struct s_room   **links;
    unsigned long   total_links;
}	t_room;

typedef struct s_data {
    unsigned short  visual;
    unsigned short  help;
    unsigned short  no_map;
    unsigned short  section_links;
    unsigned short  section_rooms;
    unsigned short  hashtable_created;
    unsigned long   ants;
    unsigned long   size_list;
    t_room          **hashtab;
    char            *start_room_name;
    char            *end_room_name;
}				t_data;

void	save_command(char *line, t_data **data, t_room **rooms);
void    save_room(char *line, t_data **data, t_room **room);
void    save_links(char *line, t_data **data, t_room **rooms);

typedef void			(*t_line_dispatcher)\
			(char *line,t_data **data, t_room **rooms);
static t_line_dispatcher	g_line_dispatch[3] = {
    save_room,
    save_command,
    save_links,
};

/*init_value*/
t_data  *set_data(t_data *node);
t_room  *set_room(char *line, char letter, t_room *room);

/*panic*/
void    panic(char *message);
unsigned short data_is_ok(t_data *data);

/*malloc_handler*/
t_data  *create_data();
t_room  *new_node(char *line, char letter);
void	create_hashtable(t_data **data);
void    create_links(t_room **room);
t_room **brealloc(t_room **links,t_room *to, unsigned long size_list);

/*free_handler*/
t_room	*my_clean(t_room *list);
void    clean2str(char *s1, char *s2);
t_data	*data_cleaner(t_data *data);
t_room	*my_clean_data(t_room *list);

/*mapreader*/
void    mapreader(t_room **rooms, t_data **data);
unsigned short	type_of_line(char *line, t_data *data);

/*get_ants*/
unsigned long	get_ants(t_data **data);

/*exit_parsing*/
void    exit_parsing(t_room *rooms, t_data *data);

/*hashtable*/
t_room *search_for(char *name, t_data *data);
void	hashtable_main(t_data **data, t_room *li);
unsigned long	hashing(char *str, unsigned int size);

/*save_data*/
// void	save_command(char *line, t_data **data, t_room **rooms);
// void    save_room(char *line, t_data **data, t_room **room);
// void    save_links(char *line, t_data **data, t_room **rooms);

/*save_data_tools*/
void	insert_links(t_room *room1, t_room *room2);

/*tools*/
char    *save_name(char *line);
void    print_line(char *line);
t_room  *push_front(t_room *list, t_room *element);
unsigned long	save_abscisse(char *line);
unsigned long	save_ordonne(char *line);


/*TOREMOVE*/
void    print_lst(t_room *li);
char	*cpy_line(char *line, char *map); //  pas necessaire
// void	print_connexion(t_data **data);
void	print_hashtab(t_data *data);


#endif