#include "parsing.h"

int     get_ants(t_data *data)
{
    int ants;
    char *line;

    line = NULL;
    get_next_line(0, &line);
    ants = ft_atoi(line);
    ft_strdel(&line);
    if (ants == 0)
        check_data(data);
    return (ants);
}