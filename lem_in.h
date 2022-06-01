/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:37:29 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/01 15:37:31 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"

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

#endif
