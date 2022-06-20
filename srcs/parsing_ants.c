#include "parsing.h"

int     get_ants()
{
    int ants;
    char *line;

    line = NULL;
    get_next_line(0, &line);
    ants = ft_atoi(line);
    free(line);
    line = NULL;
    return (ants);
}