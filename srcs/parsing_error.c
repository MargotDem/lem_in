#include "parsing.h"

void    mem_error(char *message, char *where, int line)
{
    /*doit diriger vers la sdterr*/
    printf("In %s: line %d:\n%s%s%s\n", where, line, "\x1B[31m",message, "\033[0m");
    exit(EXIT_FAILURE);
}