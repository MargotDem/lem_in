#include "parsing.h"


t_room *search_for(char *connexion, t_data **data)
{
	unsigned long index;
	t_room *temp;

	index = hashing(connexion,(*data)->size_lst);
	temp = (*data)->hashtab[index];
	while (ft_strcmp(connexion, temp->room_name) != 0)
		temp = temp->h_next;
	return (temp);
}

void add_links(t_data **data, char *from, char *to)
{
	
	int index;
	t_room *temp;

	index =  hashing(from,(*data)->size_lst);
	temp = (*data)->hashtab[index];
	while (ft_strcmp(from, temp->room_name) != 0)
		temp = temp->h_next;
	create_links(temp, to, data);
	printf("%sTEMP -> %s || CONEX-> %s\n%s", "\x1B[35m", temp->room_name, from, "\x1B[0m");

}

int	existing_room(char *conexion, t_data **data)
{
	int count;
	unsigned long index;
	t_room *tmp;

	count = 0;
	index = hashing(conexion,(*data)->size_lst);
	tmp = (*data)->hashtab[index];
	while(tmp != NULL)
	{
		if(ft_strcmp(conexion, tmp->room_name) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return(FALSE);

}

int	index_of_chr(char *str, char c)
{
	int	i;

	i = 0;
	if(str[0] == c)
		return (-1);
	while (str[i] != '\0')
	{
		if ( c == str[i])
			return (i);
		i++;
	}
	return (-1);
}
