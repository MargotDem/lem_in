#include "parsing.h"

static int basic_connexioncheck(/*char *line,*/ int active_room);
// static int shape_connexioncheck(char *line);
// static int recurrence(char *line, char c);


// static int recurrence(char *line, char c)
// {
//     int i;
//     int count;

//     count = 0;
//     i = 0;
//     while (line[i] != '\0')
//     {
//         if (line[i] == c)
//             count += 1;
//         i++;
//     }
//     if (count != 1)
//         return (1);
//     return (0);
// }

static int basic_connexioncheck(/*char *line,*/ int active_room)
{
    if (active_room == 0)
        return (1);
    // if (ft_strchr(line, '-') == NULL)
    //     return (1);
    return (0);
}

// static int shape_connexioncheck(char *line)
// {
//     int i;

//     i = 0;
//     if (recurrence(line, '-'))
//         return (1);
//     while (line[i] != '\0')
//     {
//         if (ft_iswhitespace(line[i]))
//             return(1);
//         i++;
//     }
//     return (0);
// }

int is_a_connexion(char *line, int active_room)
{
    (void)line;
    if (basic_connexioncheck(/*line,*/ active_room))
        return (0);
    // if (shape_connexioncheck(line))
    //     return (0);
    return (1);
}

void    get_connexion(t_room **li, char *line)
{
    (void)li;
    (void)line;
    printf("C est une connexion...\n");

}