#include "parsing.h"

void    print_line(char *line, int size)
{
    // size_t  length;

    // length = ft_strlen(line);
    write (1, line, size);
    write (1, "\n", 1);
}

char    *save_name(char *line)
{
    size_t  i;
    char    *name;

    i = 0;
    while (line[i] > 32)
        i++;
    name = ft_strsub(line, 0, i);
    if (!name)
        panic("In tools.c: save_name");
    return (name);
}

unsigned long	save_abscisse(char *line)
{
	size_t	i;

	i = 0;
    while (ft_iswhitespace(line[i]))
        i++;
    while (line[i] > 32)
        i++;
	return (ft_atoi(&line[i]));
}

unsigned long	save_ordonne(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (ft_isdigit(line[i]))
		i--;
	return (ft_atoi(&line[i]));
}

t_room  *push_front(t_room *list, t_room *element)
{
    if (list == NULL)
        return (element);
    element->next = list;
    return (element);
}





/* ============================= TO REMOVE ==========================*/

void    print_lst(t_room *li)
{
    t_room *temp;

    temp = li;
    while (li != NULL)
    {
        printf("room name: %s\n", li->name);
        printf("Line: %lu && Row: %lu\n", li->abscisse, li->ordonne);
        if (li->end)
            printf("This is the ending room\n");
        else if (li->start)
            printf("This is the starting room\n");
        else
            printf("This is the normal room\n");

        printf("--------------------------------\n");
        li =li->next;
    }
}

// void	print_connexion(t_data **data)
// {
// 	int i = 0, x = 0;
// 	t_room *temp = NULL;

// 	while ( i < (*data)->size_lst)
// 	{
// 		temp = (*data)->hashtab[i];
// 		if (temp != NULL)
// 		{
// 			while (temp != NULL)
// 			{
// 				printf("\nROOM NAME: %s || index %d\n", temp->name, i);
// 				printf("\tConnexion: total:%d\n",temp->nb_links);
// 				if (temp->nb_links == 0)
// 					printf("\tnull");
// 				else
// 				{
// 					x = 0;
// 					while (x < temp->nb_links)
// 					{
// 						printf("\ttemp->links[%d]->name: %s\n", x,temp->links[x]->name);
// 						x++;
// 					}
// 				}
// 				temp = temp->h_next;
// 			}
// 		}
// 		i++;
// 	}
// }

void	print_hashtab(t_data *data)
{
	size_t	i;
	t_room	*temp;

	i = 0;
	temp = NULL;
	while (i < data->size_list)
	{
		temp = data->hashtab[i];
		if (temp != NULL)
		{
			while (temp != NULL)
			{
				printf("VALEUR -> %s || INDEX -> %zu\n", temp->name, i);
				temp = temp->hash_next;
			}
		}
		i++;
	}
}