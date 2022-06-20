#include "parsing.h"

void    *ft_cleanstr(char **s, size_t i)
{
    size_t  j;

    j = 0;
    while (j < i)
    {
        free(s[j]);
        j++;
    }
    free(s);
    return (NULL);
}