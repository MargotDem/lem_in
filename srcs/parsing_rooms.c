#include "parsing.h"

static int  basic_roomcheck(char *line, int active_connextion);
static int  shape_roomcheck(char *line);
static int  word_roomcheck(char *line);

void   get_room(t_room **li, char *line, t_data **data)
{
    t_room  *element;
    printf("%s================%s========================%s\n\n", "\x1B[33m", "NODE CREATION", "\x1B[0m");
    element = new_node(line, 'n');
    if (!element)
        err_handling("new node");
	// marg the push function already checks if li == null return element
    if (*li == NULL)
        *li = element;
    else
        *li = push(*li, element);
    (*data)->size_lst += 1;
    (*data)->room_part = 1;
    printf("\n%s================   END ========================%s\n", "\x1B[33m", "\x1B[0m");
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
