#include "parsing.h"

/*Skip space*/
int	skip_space(char *line)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	return (i);
}

/*Skip a word*/
int	skip_word(char *line)
{
	int	i;

	i = 0;
	while (line[i] > 32)
		i++;
	return (i);
}

int	check_space(char *line, int i)
{
	int	count;

	count = 0;
	if (line[i] == ' ')
	{
		count += 1;
		if (count == 1)
		{
			if (!ft_isprint(line[i - 1]) && !ft_isdigit(line[i + 1]))
				return (1);
		}
		else
		{
			if (!ft_isdigit(line[i + 1]) && !ft_isdigit(line[i - 1]))
				return (1);
		}
	}
	return (0);
}

t_room	*set_startorend(t_room *element, char c)
{
	if (c == 'e')
	{
		element->room_end = 1;
		element->room_start = 0;
	}
	else if (c == 's')
	{
		element->room_end = 0;
		element->room_start = 1;
	}
	else
	{
		element->room_end = 0;
		element->room_start = 0;
	}
	return (element);
}
