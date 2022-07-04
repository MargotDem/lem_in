#include "lem_in.h"

// int	countwords(char const *s, char c);
// int check_digit(char *str);
// int check_name(char *str);
// void	*ft_cleanstr(char	**s, size_t	i );
// void print_lst(t_room *li);
// char *extract_name(char *line);
// int extract_line(char *line);
// int extract_row(char *line);
// t_room     *new_node(char *line);
// t_room  *set_pointer(t_room *li, t_room *element);
// int skip_word(char *line);
// int skip_space(char *line);
// void set_struct_data(t_data *data);
// void set_struct_room(t_room *room);

/*---------------------- COMMENT ----------------------------------*/

/*applique rule pour le comment*/
/*PAS SUR DE LA NECESSITE DE CETTE FONCTION*/
void get_comment(t_room **li, t_data **data, char *line)
{
     printf("get_comment  in ----------------------\n");
    (void)li;
    (void)data;
    get_next_line(0, &line);// verifier si cela ne fait pas passer une ligne de trop
    free(line);
    line = NULL;
     printf("get_comment  out ----------------------\n");
}

/*Analyse line pour definir si line est a valide comment*/
int is_a_comment(char *line,t_data *data)
{
     printf("is_a_comment in ----------------------\n");
    int i;
    (void)data;

    i = 0;
    if(line[0] == '#' && line[1] != '#')
        return (1);
    printf("is_a_comment  out ----------------------\n");
    return (0);
}

/* ------------------------------   ROOM  ------------------------------------*/

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

/*Place la nouvelle node dans la liste*/
t_room *push(t_room *li, t_room *element)
{
    printf("PUSH  IN ----------------------\n");
    t_room *head;

    head = li;
    if (ft_strcmp(li->name, element->name) > 0)
    {
        element->next = li;
        li = element;
        return(li);
    }
    while (li->next != NULL)
    {
        if (ft_strcmp(li->name, element->name) < 0 && \
        ft_strcmp(element->name, li->next->name) < 0)
            break;
        li = li->next;
    }
    li = set_pointer(li, element);
    printf("PUSH  OUT ----------------------\n");
    return (head);

}

/*Creer une liste en ordre ascending*/
void    get_room(t_room **li,t_data **data, char *line)
{
    printf("GET ROOMS  IN ----------------------\n");
    t_room *element;
    (void)data;

    element = new_node(line);
    if(*li == NULL)
        *li =  element;
    else
        *li = push(*li, element);
    printf("GET ROOMS  OUT ----------------------\n");
    // return (li);
}

/*----------------------------   GET ANT --------------------------------------*/

/*Recupere le nombre de fourmi*/
int get_ants(char *line)
{
    int ants;
    printf("GET ANTS  IN ----------------------\n");
    get_next_line(0, &line);
    ants = ft_atoi(line);
    printf("GET ANTS  OUT ----------------------\n");
    return (ants);
}

/*--------------------------- CONNEXION -----------------------------------*/

// int basic_connexioncheck(char *line, t_data *data)
// {
//     int i;

//     i = 0;
//     if(data->room_part == 0)
//         return (0);
//     if (!ft_strchr(line, '-'))
//         return (0);
//     while (line[i] != '\0')
//     {
//         if(!ft_isprint(line[i]))
//             return (0);
//             i++;
//     }
//     return (1);
// }



// int is_connexion(char *line, t_data *data)
// {
//     if (basic_connexioncheck(line, data))
//         return (0);
    
//     return (1);
// }

/*------------------------------- IDENTIFIER UNE LINE ---------------------*/
/*Set les varaibles des functions a zero pout data*/
void set_struct_data(t_data *data)
{
    data->room_part = 0;
    data->connexion_part = 0;
    data->room_start = 0;
    data->room_end = 0;
    data->ants = 0;
}

void set_struct_room(t_room *room)
{
    room->name = "\0";
    room->line = 0;
    room->row = 0;
    room->next = NULL;
}


/*Identifie si line = comment, room, ou connexion et definie sa validite*/
int line_id(char *line, t_data *data)
{
    printf("LINE ID  IN ----------------------\n");
    if (is_a_comment(line, data))
{        printf("LINE ID  OUT 0 ----------------------\n");
        return (0);}
    else if (is_a_room(line, data))
    {
        data->room_part = 1;
        printf("LINE ID  OUT  1 ----------------------\n");
        return(1);
    }
    // else if (is_a_connexion(line, data))
    // {
    //     data->connexion_part = 1;
    //     return (2);
    // }
    // else if (is_a_command(line, data))
    //     return (3);
    else
{        printf("LINE ID  OUT  4 ----------------------\n");
        return(4);}
}



/*READ MAP IN FD 0 and store info into link list*/
void mapreader(int fd, t_room **li, t_data **data)
{
    char *line = NULL;
    int temp = 0;
    printf("MAPREADER  IN ----------------------\n");
    (*data) = (t_data *)malloc(sizeof(**data)); // A deplacer dans une function
    (*data)->ants = get_ants(line);
    while(get_next_line(fd, &line))
    {
        printf("LINE -->%s\n", line);
        temp = line_id(line, *data);
        if (temp > 1)
            printf("Vers les autres options\n");
        else
            line_dispatch[temp](li, data, line);
    }
    free(line);
    line = NULL;
    printf("MAPREADER  OUT ----------------------\n");
    // return (*li);
}

/*----------------------------- BINARY TREE --------------------------------------------*/

/*Set un arbre binaire tree*/
// void create_btree(t_room **lst_room)
// {
    
// }


/*============================= MAIN  =================================================*/

int main(void)
{
    t_room *lst_room;
    t_data *data;

    // set_struct_data(&data);
    // set_struct_room(&lst_room);
    lst_room = NULL;
    data = NULL;
    mapreader(0, &lst_room, &data);
    printf("There is %d ants\n", data->ants);
    print_lst(lst_room);
    // create_btree(&lst_room);
    return (0);
}

/*====================================================================================*/

/*UTILS FUNCTIONs*/
/*Set les varaibles des functions a zero pout data*/
// void set_struct_data(t_data *data)
// {
//     data->room_part = 0;
//     data->connexion_part = 0;
//     data->room_start = 0;
//     data->room_end = 0;
//     data->ants = 0;
// }

// void set_struct_room(t_room *room)
// {
//     room->name = "\0";
//     room->line = 0;
//     room->row = 0;
//     room->next = NULL;
// }

/*organise les pointers lors de la creation de la liste*/
t_room  *set_pointer(t_room *li, t_room *element)
{
    if(li->next == NULL)
        li->next = element;
    else
    {
        element->next = li->next;
        li->next = element;
    }
    return (li);
}

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


/*Create a new node*/
t_room     *new_node(char *line)
{
    t_room *tr;

    tr = malloc(sizeof(*tr));
    if (tr == NULL)
    {
        write (2, "ERROR MALLOC\n", 13);
        exit(EXIT_FAILURE);
    }
    tr->name = extract_name(line);
    tr->line = extract_line(line);
    tr->row = extract_row(line);
    tr->next = NULL;
    // tr->left = NULL;
    // tr->right = NULL;
    // tr->parent = NULL;
    printf("Creation de %s avec les valeurs line = %d && row = %d\n", tr->name, tr->line, tr->row);
    return (tr);
}

/*free chaque str dans char ***/
void	*ft_cleanstr(char	**s, size_t	i )
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free (s[j]);
		j++;
	}
	free (s);
	return (NULL);
}

/*count how many word in line*/
int	countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
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
            return (-1);
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
            return (-1);
        i++;
    }
    return (i);
}

/*PRINT a LIST*/
void print_lst(t_room *li)
{
    t_room *temp;
    int count = 0;
    temp = li;
    while (temp != NULL)
    {
        printf("%s - ", temp->name);
        count += 1;
        temp = temp->next;
    }
    printf("\n");
    printf("There is %d nodes\n", count);
}

// /*Skip space*/
int skip_space(char *line)
{
    int i;
    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    return (i);
}

// /*Skip word*/
int skip_word(char *line)
{
    int i;
    i = 0;
    while(line[i] > 32)
        i++;
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

 if(check_name(&line[i]) < 0)
        return (0);
    else
        i += check_name(&line[i]);
    if(line[i] == ' ' &&  ft_iswhitespace(line[i + 1]))
        return (0);
    i++;
    if (check_digit(&line[i]) < 0)
        return (0);
    else
        i += check_digit(&line[i]);        
    if(line[i] == ' ' &&  ft_iswhitespace(line[i + 1]))
        return (0);
    i++;
    if (check_digit(&line[i]) < 0)
        return (0);
    else
        i += check_digit(&line[i]);   
    if (line[i] != '\0')
        return (0);
*/