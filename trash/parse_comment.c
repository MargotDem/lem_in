#include "lem_in.h"


/*applique rule pour le comment*/
/*PAS SUR DE LA NECESSITE DE CETTE FONCTION*/
void get_comment(t_room **li, t_data **data, char *line)
{
     printf("get_comment  in ----------------------\n");
    (void)li;
    (void)data;
    get_next_line(0, &line);// verifier si cela ne fait pas passer une ligne de trop
    free(line);
    line = NULL;
     printf("get_comment  out ----------------------\n");
}

/*Analyse line pour definir si line est a valide comment*/
int is_a_comment(char *line,t_data *data)
{
     printf("is_a_comment in ----------------------\n");
    int i;
    (void)data;

    i = 0;
    if(line[0] == '#' && line[1] != '#')
        return (1);
    printf("is_a_comment  out ----------------------\n");
    return (0);
}