#include "parsing.h"

/*perror
**void perror(char *message);
*/
/*strerr
**fprintf(stderr, "message: %s\n", strerror(errno));
*/
/*exit*/

void    check_data(t_data *data)
{
    if (data->ants == 0)
        err_mes("No ants founded!\n");
    if (data->connexion_part == 0)
        err_mes("Error\n");
    if (data->size_lst == 0)
        err_mes("No rooms founded.\n");
    if(!data->exit_room || !data->start_room)
        err_mes("No starting or ending point founded.\n");
    
}

void go_to_solver(t_room **li, char *line, t_data **data)
{
    ft_strdel(&line);
    check_data((*data));
    //solve(search_for((*data)->start_room, *data), *data);
	test_solver(search_for((*data)->start_room, *data));
    free_all(data);
    free(li);
    free(data);
    exit(EXIT_SUCCESS);
}