#include "lem_in.h"

int countwordinline(char *line);
int check_digit(char *str);
int check_name(char *str);

/*PRINT a LIST*/
void print_lst(t_room *li)
{
    while (li != NULL)
    {
        printf("%s - ", li->room_name);
        li = li->next;
    }
    printf("\n");
}

/*applique rule pour le comment*/
/*PAS SUR DE LAA NECESSITE DE CETTE FONCTION*/
void    get_comment(t_room *li, t_room *data)
{
    char *line;
    (void)li;
    (void)data;
    get_next_line(0, &line);// verifier si cela ne fait pas passer une ligne de trop
    free(line);
    line = NULL;
}

/*Analyse line pour definir si line est a valide comment*/
int is_a_comment(char *line,t_room *data)
{
    int i;

    i = 0;
    if(line[0] == '#' && ft_isalpha(line[1]))
    {
        while(line[i]!= '\0')
        {
            if(!ft_isalpha(line[i]))
                return (0);
            i++;
        }
    }
    return (1);
}

/*Analyse line pour definir si line est a valide room*/
/*FUNCTION TROP GRANDE ET MOCHE*/
int is_a_room(char *line, t_data *data)
{
    int i;

    i = 0;
    if (data->connexion_part == 1)
        return (0);
    if (line[0] == '#' || line[0] == 'L' || !ft_isprint(line[0]))
        return (0);
    if (countwordinline(line) != 3) // check le nombre de mot dans line
        return (0);
    if(check_name(&line[i]) == 0)
        return (0);
    else
        i += check_name(&line[i]);
    if(line[i] == ' ' &&  ft_iswhitespace(line[i + 1]))
        return (0);
    i++;
    if (check_digit(&line[i]) == 0)
        return (0);
    else
        i += check_digit(&line[i]);        
    if(line[i] == ' ' &&  ft_iswhitespace(line[i + 1]))
        return (0);
    i++;
    if (check_digit(&line[i]) == 0)
        return (0);
    else
        i += check_digit(&line[i]);   
    if (line[i] != '\0')
        return (0);
    return (1);
}

/*Identifie si line = comment, room, ou connexion et definie sa validite*/
int line_id(char *line, t_data *data)
{
    if (is_a_comment(line, data))
        return (0);
    else if (is_a_room(line, data))
    {
        data->room_part = 1;
        return(1);
    }
    else if (is_a_connexion(line, data))
        return (2);
    else if (is_a_command(line, data))
        return (3);
    else
        return(4);
}

/*READ MAP IN FD 0 and store info into link list*/
t_room *mapreader(int fd, t_room *li, t_room *data)
{
    char *line;

    while(get_next_line(fd, &line))
        line_dispatch[line_id(line, data)](li, data);
    return (li);
}

int main(void)
{
    t_room *lst_room;
    t_data *data;
    lst_room = mapreader(0, lst_room, data);
    print_lst(lst_room);
    return (0);
}

/*UTILS FUNCTIONs*/
/*count how many word in line*/
int countwordinline(char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[i] != '\0')
    {
        while (line[i] <= 32)
            i++;
        count += 1;
        while(line[i] > 32)
            i++;
    }
    return (count);
}

/*Verifie une chaine de caractere pour savoir il y autre qu un digit*/
int check_digit(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && !ft_iswhitespace(str[i]))
    {
        if(!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (i);
}

/*Verifie une chaine de caractere pour trouver autre caratere que print*/
int check_name(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && !ft_iswhitespace(str[i]))
    {
        if(!ft_isprint(str[i]))
            return (0);
        i++;
    }
    return (i);
}

/*=====================================================================================*/
/*BRIQUE CODE*/
/*int is_a_room(char *line, t_data *data)
    // while(line[i] > 32 && line[i] != '\0')
    // {
    //     if(line[i] < 33)
    //         return(0);
    //     i++;
    // }
    --------------------------------------------
        // while (ft_isdigit(line[i]) && line[i] != '\0')
    // {
    //     if(!ft_isdigit(line[i]))
    //         return (0);
    //     i++;
    // }
*/