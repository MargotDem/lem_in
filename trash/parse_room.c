#include "lem_in.h"

/*Verifie la validite dune room*/
int basic_roomcheck(t_data *data, char *line)
{
    printf("basic_roomcheck  in ----------------------\n");
    if(data->connexion_part == 1)
{     printf("basic_roomcheck  out 1----------------------\n");
        return (1);}
    if (line[0] == '#' || line[0] == 'L' || !ft_isprint(line[0]))
{     printf("basic_roomcheck  out 1----------------------\n");
        return (1);}
    if (countwords(line, ' ') != 3) // check le nombre de mot dans line
{     printf("basic_roomcheck  out 1----------------------\n");
        return (1);}
    printf("basic_roomcheck  out ----------------------\n");
    return (0);
}

/*Verifie si le caratere avant et apres espace coorespont*/
int shape_roomcheck(t_data *data, char *line)
{
    printf("shape_roomcheck  in ----------------------\n");
    int i;
    int count;
    (void)data;
    
    i = 0;
    count = 0;
    while(line[i] != '\0')
    {
        if(line[i] == ' ')
        {
            count += 1;
            if(count == 1)
            {    if(!ft_isprint(line[i - 1]) && !ft_isdigit(line[i + 1]))
                    return(1);}
            else
            {    if(!ft_isdigit(line[i + 1]) && !ft_isdigit(line[i - 1]))
                    return (1);}
        }
        i++;
    }
    printf("shape_roomcheck  OUT ----------------------\n");
    return(0);
}

/*Verifie si chaque str est comme il se doit*/
int word_roomcheck(t_data *data, char *line)
{
    printf("WORD_ROOMCHECK  IN ----------------------\n");
    int i;
    int x;
    char **words;
    (void)data;

    i = 0;
    x = 0;
    words = ft_strsplit(line, ' ');
    while(words[i][x] != '\0')
    {
        x = 0;
        while(words[i][x] != '\0')
        {
            if (i == 0)
{                if(!ft_isprint(words[i][x]))
                    return (1);}
            else
            {    if(!ft_isdigit(words[i][x]))
                    return(1);}
            x++;
        }
        i++;
    }
    ft_cleanstr(words, 3);   
    printf("WORD_ROOMCHECK  OUT ----------------------\n");
    return (0);
}

/*Analyse line pour definir si line est a valide room*/
/*FUNCTION TROP GRANDE ET MOCHE*/
int is_a_room(char *line, t_data *data)
{
    printf("IS_A_ROOM  IN ----------------------\n");
    int i;
    int count;

    i = 0;
    count = 0;
    if (basic_roomcheck(data,line))
        return(0);
    if (shape_roomcheck(data, line))
        return (0);
    if (word_roomcheck(data, line))
        return (0);
    printf("IS_A_ROOM  OUT ----------------------\n");
    return (1);
}
