#include "parsing.h"


void	print_connexion(t_data **data)
{
	int i = 0, x = 0;
	t_room *temp = NULL;

	while ( i < (*data)->size_lst)
	{
		temp = (*data)->hashtab[i];
		if (temp != NULL)
		{
			while (temp != NULL)
			{
				ft_putstr("\nROOM NAME: ");
				ft_putstr(temp->name);
				ft_putstr(" || index ");
				ft_putnbr(i);
				ft_putstr("\tConnexion: total:");
				ft_putnbr(temp->nb_links);
				if (temp->nb_links == 0)
					ft_putstr("\tnull");
				else
				{
					x = 0;
					while (x < temp->nb_links)
					{
						ft_putstr("\ttemp->links[");
						ft_putnbr(x);
						ft_putstr("]->name: ");
						ft_putstr(temp->links[x]->name);
						ft_putstr("\n");
						x++;
					}
				}
				temp = temp->h_next;
			}
		}
		i++;
	}
}

t_room *search_for(char *connexion, t_data *data)
{
	unsigned long index;
	t_room *temp;

	index = hashing(connexion,data->size_lst);
	temp = data->hashtab[index];
	while (ft_strcmp(connexion, temp->name) != 0 && temp != NULL)
		temp = temp->h_next;
	return (temp);
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
