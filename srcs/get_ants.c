#include "parsing.h"

unsigned short	only_digit_in(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (!ft_isdigit(line[i]))
			return (FALSE);
	}
	return (TRUE);

}

// unsigned long	get_ants(t_data **data)
// {
// 	char			*line;
// 	unsigned long	ants;

// 	while (get_next_line(0, &line))
// 	{
// 		// (*data)->map = cpy_line(line,(*data)->map, *data);
// 		if (only_digit_in(line))
// 		{
//             // (*data)->map = cpy_line(line,(*data)->map, *data);
// 			ants = ft_atoi(line);
//             (*data)->ants = ants;
// 			return(ft_strdel(&line), ants);
// 		}
// 		if (type_of_line(line, *data) != 1)
// 			return (ft_strdel(&line), 0);
// 		// (*data)->map = cpy_line(line,(*data)->map, *data);
// 	}
// 	return(ft_strdel(&line), 0);
// }

unsigned long	get_ants(t_data **data)
{
	char			*line;
	unsigned long	ants;
	char			*map;
	size_t			index = 0;

	map = (*data)->map;
	while (get_line(&map[index], &line, *data))
	{
		// (*data)->map = cpy_line(line,(*data)->map, *data);
		if (only_digit_in(line))
		{
            // (*data)->map = cpy_line(line,(*data)->map, *data);
			ants = ft_atoi(line);
            (*data)->ants = ants;
			return(ft_strdel(&line), ants);
		}
		if (type_of_line(line, *data) != 1)
			return (ft_strdel(&line), 0);
		// (*data)->map = cpy_line(line,(*data)->map, *data);
		index = (*data)->index_line;
	}
	return(ft_strdel(&line), 0);
}