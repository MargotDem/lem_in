#include "lem_in.h"

/*Creer une liste en ordre ascending*/
void    get_room(t_room **li,t_data **data, char *line)
{
    printf("GET ROOMS  IN ----------------------\n");
    t_room *element;
    (void)data;

    element = new_node(line);
    if(*li == NULL)
        *li =  element;
    else
        *li = push(*li, element);
    printf("GET ROOMS  OUT ----------------------\n");
    // return (li);
}

/*----------------------------   GET ANT --------------------------------------*/

/*Recupere le nombre de fourmi*/
int get_ants(char *line)
{
    int ants;
    printf("GET ANTS  IN ----------------------\n");
    get_next_line(0, &line);
    ants = ft_atoi(line);
    printf("GET ANTS  OUT ----------------------\n");
    return (ants);
}
