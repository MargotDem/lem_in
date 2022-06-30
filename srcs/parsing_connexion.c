#include "parsing.h"

static int basic_connexioncheck(char *line, int active_room);
static int shape_connexioncheck(char *line);
static int recurrence(char *line, char c);


static int recurrence(char *line, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			count += 1;
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}

static int basic_connexioncheck(char *line, int active_room)
{
	if (active_room == 0)
		return (1);
	if (ft_strchr(line, '-') == NULL)
		return (1);
	return (0);
}

static int shape_connexioncheck(char *line)
{
	int i;

	i = 0;
	if (recurrence(line, '-'))
		return (1);
	while (line[i] != '\0')
	{
		if (ft_iswhitespace(line[i]))
			return(1);
		i++;
	}
	return (0);
}

int is_a_connexion(char *line, int active_room)
{
	if (basic_connexioncheck(line, active_room))
		return (0);
	if (shape_connexioncheck(line))
		return (0);
	return (1);
}

void    get_connexion(t_room **li, char *line, t_data **data)
{
	char *conexion_1;
	char *conexion_2;

	(*data)->connexion_part = 1;
	if ((*data)->hash == 0)
		hashtable_main(data, *li);
	conexion_1 = ft_strsub(line, 0 , index_of_chr(line, '-'));
	conexion_2 = ft_strdup(&line[(index_of_chr(line, '-')) + 1]);
	if(existing_room(conexion_1,data) && existing_room(conexion_2, data))
	{	
		add_links(data, conexion_1, conexion_2);
		add_links(data, conexion_2, conexion_1);
	}
	else
		printf("%sNOT OK%s\n", "\x1B[31m","\x1B[0m");
	// printf("=======================================\n");
	// free(conexion_1);
	// free(conexion_2);
	// conexion_1 = NULL;
	// conexion_2 = NULL;
}