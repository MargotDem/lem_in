#include "parsing.h"

/*perror
**void perror(char *message);
*/
/*strerr
**fprintf(stderr, "message: %s\n", strerror(errno));
*/
/*exit*/

int    check_data(t_data *data)
{
    t_room *g_head;
    if (data->ants == 0)
        err_mes("No ants founded!\n");
    if(!data->exit_room || !data->start_room)
        err_mes("No starting or ending point founded\n.");
    g_head = search_for(data->start_room, data);
    printf("SEND TO SOLVER\n");
    return (1);
}