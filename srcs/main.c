/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:17:19 by briffard          #+#    #+#             */
/*   Updated: 2022/10/07 13:28:27 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_letter(char letter, t_data *data)
{
	if (letter != 'v' && letter != 'm' && letter != 'h' && letter != 'p')
	{
		print_usage();
		exit_parsing(NULL, NULL, data);
	}
	else if (letter == 'v')
		data->visual = TRUE;
	else if (letter == 'm')
		data->no_map = TRUE;
	else if (letter == 'h')
		data->help = TRUE;
	else if (letter == 'p')
		data->print_paths = TRUE;
}

t_data	*check_option(int argc, char *option, t_data *data)
{
	int		i;
	char	letter;

	i = 0;
	data = create_data();
	if (!data)
		exit_parsing(NULL, NULL, data);
	set_data(data);
	if (argc == 1)
		return (data);
	if (option[0] != '-' || argc > 2)
	{
		print_usage();
		exit_parsing(NULL, NULL, data);
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
	system("leaks lem-in > int_leaks.txt");
	if (data_is_ok(data))
		solve(search_for(data->start_room_name, data), data);
	else
		handle_error();
	data = data_cleaner(data);
	system("leaks lem-in > leaks.txt");
	return (0);
}
