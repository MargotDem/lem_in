#include "parsing.h"

void	print_usage(void)
{
	write (1,"usage: lem-in [-vmh] < source_file\n",35);
}

void check_letter(char letter, t_data *data)
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
	if(option[0] != '-' || argc > 2)
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

int main(int argc, char **argv)
{
	t_room		*rooms;
	t_data		*data;

	data = NULL;
	rooms = NULL;

	data = check_option(argc, argv[1], data);
	if (data->help)
	{
		printf("MAN LEM-in\n");
		free(data);
		data = NULL;
		exit(EXIT_SUCCESS);
	}

	mapreader(&rooms, &data);
	printf("ANTS -> %lu || start -> %s || end ->%s\n", data->ants, data->start_room_name, data->end_room_name);
	if (data_is_ok(data))
		printf("GO TO SOLVER\n");
	else
		printf("error\n");
	// data = data_cleaner(data);
	system("leaks lem-in");
	return (0);
}