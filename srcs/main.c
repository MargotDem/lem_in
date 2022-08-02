/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:17:19 by briffard          #+#    #+#             */
/*   Updated: 2022/08/02 09:06:16 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_letter(char letter, t_data *data)
{
	if (letter != 'v' && letter != 'm' && letter != 'h')
	{
		print_usage();
		free(data);
		data = NULL;
		exit(EXIT_FAILURE);
	}
	else if (letter == 'v')
		data->visual = TRUE;
	else if (letter == 'm')
		data->no_map = TRUE;
	else if (letter == 'h')
		data->help = TRUE;
}

t_data	*check_option(int argc, char *option, t_data *data)
{
	int		i;
	char	letter;

	i = 0;
	data = create_data();
	set_data(data);
	if (argc == 1)
		return (data);
	if (option[0] != '-' || argc > 2)
	{
		print_usage();
		free(data);
		data = NULL;
		exit(EXIT_FAILURE);
	}
	while (option[++i] != '\0')
	{
		letter = option[i];
		check_letter(letter, data);
	}
	return (data);
}

int	main(int argc, char **argv)
{
	t_room		*rooms;
	t_data		*data;

	data = NULL;
	rooms = NULL;
	data = check_option(argc, argv[1], data);
	if (data->help)
	{
		print_man();
		free(data);
		data = NULL;
		exit(EXIT_SUCCESS);
	}
	mapreader(&rooms, &data);
	printf("START -> %s || end-> %s || ants-> %lu\n", data->start_room_name, data->end_room_name, data->ants);
	if (data_is_ok(data))
	{
		if (data->no_map == FALSE)
			write(1, data->map, data->index_line);
		printf("GO TO SOLVER MAIN\n");
	}
	else
		printf("error\n");
	data = data_cleaner(data);
	system("leaks lem-in");
	return (0);
}
