#include "parsing.h"

int	only_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_nb_ants(char *line)
{
	if (only_digit(line))
		return (TRUE);
	return (FALSE);
}

int	get_ants(t_data *data, char *line)
{
	int	ants;

	ants = 0;
	while (get_next_line(0, &line))
	{
		if (is_nb_ants(line))
		{
			ants = ft_atoi(line);
			ft_strdel(&line);
			return (ants);
		}
		if (is_comment(line) || is_connexion(line, 1) || \
		(is_room(line, 0) && ants == 0))
			check_data(data);
	}
	return (0);
}
