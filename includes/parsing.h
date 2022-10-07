/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:21:57 by briffard          #+#    #+#             */
/*   Updated: 2022/10/07 10:36:19 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*INCLUDES*/
# include "libft.h"
# include <stdio.h>
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
# define ERROR 0
# define OK 1

/*STRUCTURE*/
typedef struct s_room
{
	char			*name;
	unsigned short	start;
	unsigned short	end;
	unsigned int	abscissa;
	unsigned int	ordinate;
	struct s_room	*next;
	struct s_room	*hash_next;
	struct s_room	**links;
	unsigned int	total_links;
	int				to_be_visited;
	struct s_vector	*history;
	struct s_room	*reverse;
}				t_room;

typedef struct s_data {
	unsigned short	visual;
	unsigned short	help;
	unsigned short	no_map;
	unsigned short	print_paths;
	unsigned short	section_links;
	unsigned short	section_rooms;
	unsigned short	hashtable_created;
	unsigned long	ants;
	unsigned long	size_list;
	t_room			**hashtab;
	char			*start_room_name;
	char			*end_room_name;
	char			*map;
	int				index_line;
	int				size_map;
}				t_data;

void				save_command(char *line, t_data **data, t_room **rooms);
void				save_room(char *line, t_data **data, t_room **room);
void				save_links(char *line, t_data **data, t_room **rooms);
void				pass_comment(char *line, t_data **data, t_room **rooms);

typedef void				(*t_line_dispatcher)\
			(char *line,t_data **data, t_room **rooms);
static t_line_dispatcher	g_line_dispatch[4] = {
	save_room,
	save_command,
	save_links,
	pass_comment,
};

/*init_value*/
t_data				*set_data(t_data *node);
t_room				*set_room(char *line, char letter, t_room *room);

/*malloc_handler*/
t_data				*create_data(void);
t_room				*new_node(char *line, char letter);
int					create_hashtable(t_data **data);
void				create_links(t_room **room);
t_room				**re_alloc(t_room **links, \
					t_room *to, unsigned long size_list);

/*free_handler*/
t_room				*clean_list(t_room *list);
void				clean2str(char *s1, char *s2, char letter);
t_data				*data_cleaner(t_data *data);
t_room				*clean_hash(t_room *list);

/*mapreader*/
void				mapreader(t_room **rooms, t_data **data);
unsigned short		type_of_line(char *line, t_data *data);

/*mapreader_tools*/
char				*readmap(char *map);
unsigned short		is_room(char *line, unsigned short section_links);

/*get_ants*/
unsigned long		get_ants(t_data **data, t_room *rooms);

/*exit_parsing*/
void				exit_parsing(char *line, t_room *rooms, t_data *data);
void				panic(char *message);
unsigned short		data_is_ok(t_data *data);

/*hashtable*/
t_room				*search_for(char *name, t_data *data);
void				hashtable_main(t_data **data, t_room *li);
unsigned long		hashing(char *str, unsigned int size);

/*hashtable_malloc*/
t_room				*cpy_room(t_room *room);

/*save_data_tools*/
int				insert_links(t_room *room1, t_room *room2);

/*tools*/
char				*save_name(char *line);
void				print_line(char *line, int size);
unsigned int		save_abscissa(char *line);
unsigned int		save_ordinate(char *line);

/*list_utils.c*/
t_room				*push_front(t_room *list, t_room *element);

/*print_man*/
void				print_usage(void);
void				print_man(void);

int					get_line(char *map, char **line, t_data *data);

void				solve(t_room *graph, t_data *data);

void				handle_error(void);

#endif