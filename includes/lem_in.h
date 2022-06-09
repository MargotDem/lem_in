/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:37:29 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/09 10:57:50 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_links_list {
	char				*name;
	struct s_links_list	*next;
}	t_links_list;

typedef struct s_rooms_list {
	int					x;
	int					y;
	char				*name;
	t_links_list		*links_list;
	struct s_rooms_list	*next;
}	t_rooms_list;

typedef struct s_map {
	char			*start;
	char			*end;
	size_t			nb_ants;
	t_rooms_list	*rooms;
}	t_map;

void	handle_error(void);

// typedef struct s_room {
// 	char *name;
// 	struct s_room *left;
// 	struct s_room *right;
// 	struct s_room *parent;
// } t_room;

#endif
