/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:37:29 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/17 15:24:13 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

/*STRUCTURE*/
typedef struct s_room{
	char *room_name;
    int line;
    int row;
	
	/*POINTER LINK LIST*/
	struct s_room *next;
}	t_room;

typedef struct s_data {

    int room_part;
    int connexion_part;
    int room_start;
    int room_end;
    int ants; // ULL pour plus de possibilite
}       t_data;

/*ARRAY POINTER FUNCTION*/
void    get_comment(t_room **li, t_data **data, char *line);
void    get_room(t_room **li, t_data **data, char *line);
// t_room *get_connexion(t_room *li, t_data *data, char *line);
// t_room *get_out(t_room *li, t_data *data, char *line);
// t_room *get_command(t_room *li, t_data *data, char *line);


void (*line_dispatch[2])(t_room **,t_data **, char *) = {
    get_comment,
    get_room,
};

/*PROTOTYPE*/
/*PARSE_COMMENT.C*/
void    get_comment(t_room **li, t_data **data, char *line);
int     is_a_comment(char *line,t_data *data);

/*PARSE_ROOM.C*/
int     basic_roomcheck(t_data *data, char *line);
int     shape_roomcheck(t_data *data, char *line);
int     word_roomcheck(t_data *data, char *line);
int     is_a_room(char *line, t_data *data);

/*GET_DATA.C*/
int     get_ants(char *line);
void    get_room(t_room **li,t_data **data, char *line);

/*UTILS*/
char *extract_name(char *line);
int extract_line(char *line);
int extract_row(char *line);
int skip_space(char *line);
int skip_word(char *line);

/*UTILS_2.C*/
int	countwords(char const *s, char c);
int check_digit(char *str);
int check_name(char *str);

/*LINK_LIST.C*/
t_room      *push(t_room *li, t_room *element);
t_room      *new_node(char *line);
void        print_lst(t_room *li);
t_room      *set_pointer(t_room *li, t_room *element);

void	*ft_cleanstr(char	**s, size_t	i );
int line_id(char *line, t_data *data);
void mapreader(int fd, t_room **li, t_data **data);


#endif
