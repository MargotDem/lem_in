#include "parsing.h"

void    panic(char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}