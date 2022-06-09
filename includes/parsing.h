#ifndef PARSING_H
# define PARSING_H

/*include*/
# include <stdio.h>
# include "libft.h"

/*STRUCT*/
typedef struct s_room {
	char *name;
	int	line;
	int row;
	struct s_room *left;
	struct s_room *right;
	struct s_room *parent;
} t_room;

/*PROTOTYPE*/
t_room *mapreader(int fd, t_room *room_tree);

#endif