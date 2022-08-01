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

/*STRUCTURE*/
typedef struct s_room{
	char			*name;
	int				x;
	int				y;
	int				room_start;
	int				room_end;
	int				nb_links;
	struct s_room	*next;
	struct s_room	*parent;
	struct s_room	*h_next;
	struct s_room	**links;
	int				visited;
	int				to_be_visited;
	int				to_be_visited_stand_by;
	int				stand_by;
	int				part_of_solution;
	struct s_hist			*history;
	struct s_room	*reverse;
}					t_room;

typedef struct s_hist {
	int	counter;
	int	size;
	t_room	**arr;
}	t_hist;

typedef struct s_data {
	int				room_part;
	int				connexion_part;
	int				size_lst;
	int				hash;
	int				ants;
	struct s_room	**hashtab;
	char			*start_room;
	char			*exit_room;
	int				show_paths;
	int				visualizer;
}				t_data;

/*ARRAY POINTER FUNCTION*/
void			get_room(t_room **li, char *line, t_data **data);
void			get_connexion(t_room **li, char *line, t_data **data);
void			get_command(t_room **li, char *line, t_data **data);
void			go_to_solver(t_room **li, char *line, t_data **data);

typedef void			(*t_line_dispatcher)\
			(t_room **li, char *line, t_data **data);
static t_line_dispatcher	g_line_dispatch[4] = {
	get_room,
	get_connexion,
	get_command,
	go_to_solver,
};

/*PROTOTYPE*/
/*PARSING_ANTS*/
int				get_ants(t_data *data, char *line);

/*PARSING_ROOMS*/
int				is_room(char *line, int active_connextion);

/*PARSING_CONNEXION*/
int				is_connexion(char *line, int active_room);

/*PARSING_CONNEXION_HANDLING*/
int				room_exists(char *room, t_data **hashtab);
t_room			*search_for(char *connexion, t_data *data);
int				index_of_chr(char *str, char c);
void			print_connexion(t_data **data);

/*PARSING_MAIN*/
int				line_id(char *line, t_data *data);

/*PARSING_COMMAND*/
int				is_command(char *line);

/*HASHTABLE_MAIN*/
void			hashtable_main(t_data **data, t_room *li);
unsigned long	hashing(char *str, unsigned int size);

/*UTILS*/
int				countwords(char const *s, char c);
char			*extract_name(char *line);
int				extract_row(char *line);
int				extract_line(char *line);
int				check_word(char **arr);

/*UTILS_2*/
int				skip_word(char *line);
int				skip_space(char *line);
t_room			*set_startorend(t_room *element, char c);

/*UTILS_LIST*/
t_room			*new_node(char *line, char c);
t_room			*push_t_room(t_room *room, t_room *element);
void			print_lst(t_room *li);

/*ERROR*/
void			mem_error(char *message, char *where, int line);
void			err_handling(char *s);
void			err_mes(char *message);

/*MEM_HANDLING*/
void			*ft_cleanstr(char **s, size_t i);
void			create_link(t_room *room_1, t_room *room_2);
void			free_all(t_data **data);
void			check_data(t_data *data);
int				is_comment(char *line);
void			insert_links(t_room *room1, t_room *room2);

void	solve(t_room *graph, t_data *data);
void print_line(char *line);

#endif