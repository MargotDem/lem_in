/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:53:51 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/01 15:53:52 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

typedef struct s_path {
	int		nb_ants;
	int		*ants;
	char	**rooms;
	int		nb_rooms;
	int		nb_turns;
}	t_path;

int	calc_nb_turns(t_path path)
{
	return (path.nb_ants + path.nb_rooms - 2);
}

int	main(void)
{
	int nb_paths = 2;
	t_path	paths[2];
	int i;
	int k;
	int	longest_turns;
	t_path	path;

	(void)nb_paths;
	(void)path;

	// creating path1
	t_path	path1;

	path1.nb_ants = 3;
	path1.nb_rooms = 5;
	path1.nb_turns = calc_nb_turns(path1);

	path1.rooms = (char **)malloc(sizeof(char *) * path1.nb_rooms);
	path1.rooms[0] = "START";
	path1.rooms[1] = "A";
	path1.rooms[2] = "B";
	path1.rooms[3] = "C";
	path1.rooms[4] = "END";

	path1.ants = (int *)malloc(sizeof(int) * path1.nb_ants);

	i = 0;
	while (i < path1.nb_ants)
	{
		path1.ants[i] = -i;
		i++;
	}

	paths[0] = path1;

	// creating path2
	t_path	path2;

	path2.nb_ants = 1;
	path2.nb_rooms = 6;
	path2.nb_turns = calc_nb_turns(path2);

	path2.rooms = (char **)malloc(sizeof(char *) * path2.nb_rooms);
	path2.rooms[0] = "START";
	path2.rooms[1] = "D";
	path2.rooms[2] = "E";
	path2.rooms[3] = "F";
	path2.rooms[4] = "G";
	path2.rooms[5] = "END";

	path2.ants = (int *)malloc(sizeof(int) * path2.nb_ants);

	i = 0;
	while (i < path2.nb_ants)
	{
		path2.ants[i] = -i;
		i++;
	}

	paths[1] = path2;

	// get longest number of turns
	//longest_turns = get_longest_turns(path);
	longest_turns = 6;

	int j = 0;
	while (j < longest_turns)
	{
		printf("'");
		k = 0;
		while (k < nb_paths)
		{
			path = paths[k];
			if (j <= path.nb_turns)
			{
				i = 0;
				while (i < path.nb_ants)
				{
					(path.ants[i])++;
					if (path.ants[i] > 0 && path.ants[i] < path.nb_rooms)
					{
						printf("L%d-%s", i + 1, path.rooms[path.ants[i]]);
						printf(", ");
					}
					i++;
				}
				k++;
			}
		}
		printf("'\n");
		j++;
	}
}
