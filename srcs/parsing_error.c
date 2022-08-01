#include "parsing.h"

/*perror
**void perror(char *message);
*/
/*strerr
**fprintf(stderr, "message: %s\n", strerror(errno));
*/
/*exit*/


/*Check if we need to free stuff with exit failure*/
void    mem_error(char *message, char *where, int line)
{
    /*doit diriger vers la sdterr*/
	ft_putstr("In ");
	ft_putstr(where);
	ft_putstr(": line ");
	ft_putnbr(line);
	ft_putstr("\n");
	ft_putstr(message);
	ft_putstr("\n");
    //printf("In %s: line %d:\n%s%s%s\n", where, line, "\x1B[31m",message, "\033[0m");
    exit(EXIT_FAILURE);
}

void    err_handling(char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}

void err_mes(char *message)
{
    write(2, message, ft_strlen(message));
    exit(EXIT_FAILURE);
}