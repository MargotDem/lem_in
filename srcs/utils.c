#include "lem_in.h"

/*Extract ROOM NAME*/
char *extract_name(char *line)
{
    int i;
    int start;
    char *name;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    start = i;
    while (line[i] > 32)
        i++;
    name = ft_strsub(line, start, i - start);
    return (name);
}

/*Extract an int line from line*/
int extract_line(char *line)
{
    int i;

    i = 0;
    i += skip_space(line);
    i += skip_word(&line[i]);
    return (ft_atoi(&line[i]));
}

/*Extract row from line*/
int extract_row(char *line)
{
    int i;

    i = ft_strlen(line) - 1;
    while(ft_isdigit(line[i]))
        i--;

    return (ft_atoi(&line[i]));
}

/*Skip space*/
int skip_space(char *line)
{
    int i;
    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    return (i);
}

/*Skip word*/
int skip_word(char *line)
{
    int i;
    i = 0;
    while(line[i] > 32)
        i++;
    return (i);
}

