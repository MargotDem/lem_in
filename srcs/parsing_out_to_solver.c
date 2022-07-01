#include "parsing.h"

/*perror
**void perror(char *message);
*/
/*strerr
**fprintf(stderr, "message: %s\n", strerror(errno));
*/
/*exit*/

int check_connexion(char *start, char *exit, t_data **data)
{
    t_room *temp;

    temp = search_for(start, data);
    if (!temp->links)
        return (1);
    temp = search_for(exit, data);
    if (!temp->links)
        return (1);
    return (0);
}

int    check_data(t_data **data)
{
    if(!(*data)->exit_room || !(*data)->start_room)
    {
        err_mes("No starting or ending point founded\n.");
        return (0);
    }
    if (check_connexion((*data)->start_room, (*data)->exit_room, data))
    {
        err_mes("No connexion founded for starting room or exit room.");
        return (0);
    }
    return (1);
}