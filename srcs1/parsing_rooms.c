#include "parsing.h"

static int  basic_roomcheck(char *line, int active_connextion);
static int  shape_roomcheck(char *line);
static int  word_roomcheck(char *line);

void   get_room(t_room **room, char *line, t_data **data)
{
	t_room  *element;
	element = new_node(line, 'n');
	if (!element)
		err_handling("new node");
	*room = push_t_room(*room, element);
	(*data)->size_lst += 1;
	(*data)->room_part = 1;
	//printf("Node %s created\n", element->name);
}

static int  basic_roomcheck(char *line, int active_connextion)
{
	if (active_connextion == 1)
		return (1);
	if (line[0] == '#' || line[0] == 'L' || !ft_isprint(line[0]))
		return (1);
	if (countwords(line, ' ') != 3)
		return (1);
	return (0);
}

static int  shape_roomcheck(char *line)
{
	int i;

	i = 0;
	if (!ft_isprint(line[0]))
		return (1);
	while (line[i] > 32)
		i++;
	if(line[i] == ' ' && !ft_isdigit(line[i + 1]))
		return (1);
	while (line[i] > 32)
		i++;
	if(line[i] == ' ' && !ft_isdigit(line[i + 1]))
		return (1);
	while (line[i] != '\0')
		i++;
	if (line[i - 1] < 33)
		return (1);
	return (0);
}

static int  word_roomcheck(char *line)
{
	int i;
	int x;
	char **words;

	i = 0;
	x = 0;
	words = ft_strsplit(line, ' ');
	if (check_word(words))
		return (1);
	ft_cleanstr(words, 3);
	return (0);
}

int is_room(char *line, int active_connextion)
{
	if(basic_roomcheck(line, active_connextion))
		return(FALSE);
	if (shape_roomcheck(line))
		return (FALSE);
	if (word_roomcheck(line))
		return (FALSE);
	return (TRUE);
}
