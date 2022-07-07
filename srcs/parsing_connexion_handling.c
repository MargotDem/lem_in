#include "parsing.h"

void	print_connexion(t_data **data)
{
	int		i = 0, x = 0, size = (*data)->size_lst;
	int		links_nb;
	t_room	*temp = NULL;

	while (i < size)
	{
		temp = (*data)->hashtab[i];
		if (temp != NULL)
		{
			while (temp != NULL)
			{
				links_nb = temp->nb_links;
				printf("\nROOM NAME: %s || index %d\n", temp->name, i);
				printf("\tConnexion: total:%d\n", links_nb);
				if (links_nb == 0)
					printf("\tnull");
				else
				{
					x = 0;
					while (x < links_nb)
					{
						printf ("\ttemp->links[%d]->name: %s\n", x, temp->links[x]->name);
						x++;
					}
				}
				temp = temp->h_next;
			}
		}
		i++;
	}
}

t_room	*search_for(char *connexion, t_data *data)
{
	unsigned long	index;
	t_room			*temp;
	int				size;

	size = data->size_lst;
	index = hashing(connexion, size);
	temp = data->hashtab[index];
	while (ft_strcmp(connexion, temp->name) != 0 && temp != NULL)
		temp = temp->h_next;
	return (temp);
}

int	index_of_chr(char *str, char c)
{
	int	i;

	i = 0;
	if (str[0] == c)
		return (-1);
	while (str[i] != '\0')
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}
