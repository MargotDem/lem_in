#include "parsing.h"

static int command_id(char *line);
static int check_command(char *line, char *command);

static int check_command(char *line, char *command)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] != command[i])
            return (0);
        i++;
    }
    return (1);
}

static int command_id(char *line)
{
    if (check_command(line, "start") || check_command(line, "end"))
            return (1);
    return (0);
}

int is_a_command(char *line)
{
    if (line[0] == '#' && line[1] == '#')
    {
        if (command_id(&line[2]))
            return (1);
    }
    return(0);
}

void    get_command(t_room **li, char *line, t_data **data)
{
    t_room *element;
    
    if (check_command(&line[2], "start"))
    {
        get_next_line(0, &line);
        if (is_a_room(line, 0))
        {           
            element = new_node(line, 's');
            *li = push(*li, element);
            (*data)->size_lst += 1;
            (*data)->start_room = extract_name(line);
        }
    }
    else if (check_command(&line[2], "end"))
    {
        get_next_line(0, &line);
        if (is_a_room(line, 0))
        {
            element = new_node(line, 'e');
            *li = push(*li, element);
            (*data)->size_lst += 1;
        }
    }
    free(line);
    line = NULL;
}