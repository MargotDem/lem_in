#include "parsing.h"

static int  basic_roomcheck(char *line, int active_connextion);
static int  shape_roomcheck(char *line);
static int  word_roomcheck(char *line);

void   get_room(t_room **li, char *line)
{
    t_room  *element;
    
    element = new_node(line);
    if (*li == NULL)
        *li = element;
    else
        *li = push(*li, element);
}

static int  basic_roomcheck(char *line, int active_connextion)
{
    if (active_connextion == 1)
        return (1);
    if (line[0] == '#' || line[0] == 'L' || !ft_isprint(line[0]))
        return (1);
    if (countwords(line, ' ') != 3)
        return (1);
    return (0);
}

static int  shape_roomcheck(char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[i] != '\0')
    {
        if (line[i] == ' ')
        {
            if (count == 0)
            {
                count += 1;
                if (!ft_isprint(line[i - 1]) && !ft_isdigit(line[i + 1]))
                    return (1);
            }
            else
            {   
                if(!ft_isdigit(line[i + 1]) && !ft_isdigit(line[i - 1]))
                    return (1);
            }
        }
        i++;
    }
    return (0);
}

static int  word_roomcheck(char *line)
{
    int i;
    int x;
    char **words;

    i = 0;
    x = 0;
    words = ft_strsplit(line, ' ');
    if (check_word(words))
        return (1);
    ft_cleanstr(words, 3);
    return (0);
}

int is_a_room(char *line, int active_connextion)
{
    if(basic_roomcheck(line, active_connextion))
        return(0);
    if (shape_roomcheck(line))
        return (0);
    if (word_roomcheck(line))
        return (0);
    return (1);
}
