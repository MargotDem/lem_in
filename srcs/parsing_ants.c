#include "parsing.h"

int     get_ants()
{
    int ants;
    char *line;

    line = NULL;
    get_next_line(0, &line);
    ants = ft_atoi(line);
	// marg should we have a util or libft function to free(ptr) and then ptr = NULL ?
    free(line);
    line = NULL;
    return (ants);
}