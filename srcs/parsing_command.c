#include "parsing.h"

static int command_id(char *line);
// static int check_command(char *line, char *command);

// static int check_command(char *line, char *command)
// {
//     int i;

//     i = 0;
//     while (line[i] != '\0')
//     {
//         if (line[i] != command[i])
//             return (0);
//         i++;
//     }
//     return (1);
// }

static int command_id(char *line)
{
	// marg ft_strncmp // correcd
    //if (check_command(line, "start") || check_command(line, "end"))
    if ((ft_strcmp(line, "start") != 0) || (ft_strcmp(line, "end") != 0))
            return (1);
    return (0);
}

int is_command(char *line)
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
    
    //Do we need to reccheck if line is a command ????
    // if (check_command(&line[2], "start"))
    // if (ft_strcmp(&line[2], "start") == 0) // Faster ?= if (line[2] == 's')
    if (line[2] == 's')
    {
        get_next_line(0, &line);
        if (is_room(line, 0))
        {    
            element = new_node(line, 's');
            *li = push_t_room(*li, element);
            (*data)->size_lst += 1;
            (*data)->start_room = extract_name(line);
        }
		// marg should we display an error message if we have
		// the start comment but no room afterwards? same for end
        /*
        ** What 's happend if we have two times the command start.
        */
    }
    // else if (check_command(&line[2], "end"))
    // else if(ft_strcmp(&line[2], "end") == 0)// Faster ?= if (line[2] == 'e')
    else if (line[2] == 'e')
    {
        get_next_line(0, &line);
        if (is_room(line, 0))
        {
            element = new_node(line, 'e');
            *li = push_t_room(*li, element);
            (*data)->size_lst += 1;
            (*data)->exit_room = extract_name(line);
        }
    }
    ft_strdel(&line);
}