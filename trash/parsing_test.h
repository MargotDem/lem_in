#ifndef PARSING_H
# define PARSING_H

/*include*/
# include <stdio.h>
# include "libft.h"

/*STRUCT*/
typedef struct s_room {
	char *name;
	int start_room;
	int end_room;
	int	line;
	int row;

	/*link_list pointer*/
	struct s_room *next;
	/*graph pointer*/
	struct s_room *g_next;
	struct s_room *g_preview;
	/*B_tree pointer*/
	struct s_room *left;
	struct s_room *right;
	struct s_room *parent;
} t_room;

/*UTILISER POUR LE PARSING*/
typedef struct lst_room {
	char *name;
	struct lst_room *next;
} t_lst_room;

 typedef struct data_lst_room {
	 int size;
	 int median;
 } t_data_lst_room;

/*PROTOTYPE*/
t_room *mapreader(int fd, t_room *room_tree);

#endif