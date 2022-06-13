#include "lem_in.h"
#include "parsing.h"


// void clean_tree(t_room *tr)
// {
//     if (tr == NULL)
//         return ;
//     printf("Suppression de %d\n", tr->name);

//     clean_tree(tr->left);
//     clean_tree(tr->right);

//     free(tr);

// }

/*remove an element from the beginning of the list*/
t_lst_room	*pop_front_list(t_lst_room *li)
{
	t_lst_room		*element;

	element = (t_lst_room *)ft_memalloc(sizeof(*element));
	if (!element)
	{
		ft_putendl_fd("Error: allocation memory", 2);
		return (NULL);
	}
	if (!li)
		return (li);
	element = li->next;
	ft_memdel((void **)&li);
	return (element);
}

/*clear all the list*/
t_lst_room	*clear_list(t_lst_room *li)
{
	if (!li)
		return  (li);
	while (li->next != NULL)
		li = pop_front_list(li);
    free(li);
    li = NULL;
	return(li);
}

/*PRINT a LIST*/
void print_lst(t_lst_room *li)
{
    while (li != NULL)
    {
        printf("%s - ", li->name);
        li = li->next;
    }
    printf("\n");
}

t_room *insert(t_room *element,t_room *tr)
{
    t_room *temp;
    temp = tr;
    if ((ft_strcmp(element->name,tr->name) < 0) && temp->left != NULL) // creer un comparateur ascii
        insert(element, temp->left);
    else if ((ft_strcmp(element->name,tr->name) > 0) && temp->right != NULL)
        insert(element, temp->right);
    element->parent = temp;
    if (ft_strcmp(element->name,tr->name) < 0)
        temp->left = element;
    else if (ft_strcmp(element->name,tr->name) > 0)
        temp->right = element; 
    return (tr);
}


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

/*Check if line is a room*/
int is_room(char *line)
{
    if (line[0] == '#')
        return (0);
    else if (countwordinline(line) != 3) // check le nombre de mot dans line
        return (0);
    return (1);
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

    i = ft_strlen(line);
    while(line[i] == ' ' || line[i] == '\t')
        i--;
    while (line[i] > 32)
        i--;
    return (ft_atoi(&line[i]));
}

/*Creer un node pointeur sur NULL*/
t_room     *new_tree(char *line)
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
    tr->left = NULL;
    tr->right = NULL;
    tr->parent = NULL;
    printf("Creation de %s avec les valeurs line = %d && row = %d\n", tr->name, tr->line, tr->row);
    return (tr);
}

t_room *insert_node(t_room *tr, char *line)
{
    t_room *element = new_tree(line);
    if (tr == NULL)
        return (element);
    printf("-->%d\n",ft_strcmp(element->name,tr->name));
    if (ft_strcmp(element->name,tr->name) < 0) // check if room est plus grand ou plus en ASCII plus petit va vers la gauche plsu vers la droite
        insert(element, tr->left);
    else
        insert(element,tr->right);
    return (tr);    
}

/*INSERT un element dans list puis le place a la fin*/
t_lst_room *push_back(t_lst_room *li, char *name)
{
    t_lst_room *element;
    t_lst_room *temp;


    element = malloc(sizeof(*element));
    element->name = ft_strdup(name);
    element->next = NULL;
    if (li == NULL)
        return (element);
    temp = li;
    if(ft_strcmp(temp->name, element->name) > 0)
    {
        element->next = temp;
        li = element;
        return (li);
    }
    while (temp->next != NULL)
    {
        if (ft_strcmp(temp->name, element->name) <  0 && ft_strcmp(element->name, temp->next->name) < 0)
            break;
        temp = temp->next;
    }
    if (temp->next == NULL)
        temp->next = element;
    else
    {
        element->next = temp->next;
        temp->next = element;
    }
    return (li);
}

/*SET DATA SIZE ET MEDIAN VALUE DE  LA LIST*/
t_data_lst_room *set_data(t_lst_room *li, t_data_lst_room *data)
{
    t_lst_room *head;

    head = li;
    data->size = 0;
    while (li != NULL)
    {
        data->size += 1;
        li = li->next;
    }
    data->median = (data->size / 2);
    return (data);
}

/*Cherche la valeur a un index donee*/
char *look_in_lst(int index, t_lst_room *li)
{
    int i;

    i = 0;
    t_lst_room *temp;

    temp = li;
    while(i != index)
    {
        temp = temp->next;
        i++;
    }
    return (temp->name);
}

/*Verifie si la line ant correspond au critere*/
int is_not_valid_ant_line(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] > 57 && line[i] < 48)
            return (1);
        i++;
    }
    return (0);
}

/*Check line pour trouver le nombre de fourmis*/
int get_ant_number(char *line)
{
    int ants;

    ants = 0;
    ants = ft_atoi(line);
    if(is_not_valid_ant_line(line) || ants == 0)
    {
        ft_putendl_fd("ERROR\n", 2);
        exit(EXIT_FAILURE);
    }
    return(ants);
}

/*Recupere les room et les stores dans une liste chainee dans ordre alphabetique*/
t_lst_room *get_room_and_connection(char *line, int fd)
{

    while(get_next_line(fd, &line))
    {
        /*si ce nest pas une room*/
            /*verifie si cest une connection*/
                /*si connextion store connections dans la room*/
                /*si la prochaine ligne est different de connextion*/
                    /*le parsing stop*/
                /*si non arrete le parsin*/     
    }
    
}


/* Lis depuis le fd = 0 et check chaque ligne */
t_room *mapreader(int fd, t_room *room_tree)
{
    char *line;
    char *name;
    int total_ants;
    t_lst_room *lst_room = NULL;

    get_next_line(0, &line);
    total_ants = get_ant_number(line); //ERROR GERER DANS IS_NOT_ANT

    lst_room = get_room_and_connection(line, fd);
    // while (get_next_line(fd, &line))// checker sur fd lire 
    // {

    //     if (is_room(line))
    //     {   
    //         name = extract_name(line);
    //         lst_room = push_back(lst_room, name);
    //     }
        // else if (is_comment(line))
        //     pass_line();
        // else if (is_modif(line))
        //     to_modif(line, room_tree);
        // else if (is_connection(line))
        //     counter_connection(line, room_tree);
    // }
    // data_room = set_data(lst_room, data_room);
    // value = data_room->median;
    // while ( value   < data_room->size)
    // {
    //     if (value == data_room->size - 2)
    //         break;
    //     if (value <= 2)
    //     {
    //         x = 1;
    //         value = data_room->median;
    //     }
    //     if (value <= data_room->median && x == 0)
    //         value /= 2;
    //     else
    //         value = ((data_room->size - value) / 2 )+ data_room->median;
    // }
    // room_tree = insert_node(room_tree, line);
    print_lst(lst_room);
    free(name);
    lst_room = clear_list(lst_room);
    free(line);
    return(room_tree);
}

/*Print en prefix de gauche a droite*/
void print_tree_prefix(t_room *tr)
{
    if (tr == NULL)
        return ;
    if (tr->parent != NULL)
        printf("(%s) -> %s \n", tr->parent->name, tr->name);
    else
        printf("(%s)\n", tr->name);
    if (tr->left != NULL )
        print_tree_prefix(tr->left);
    if (tr->right != NULL)
        print_tree_prefix(tr->right);
}

int main(void)
{
    t_room *room_tree = NULL;
    room_tree = mapreader(0, room_tree);
    print_tree_prefix(room_tree);


    /*
    ** compilatyion type ./lem-in < map.txt
    ** argv renvoie une addresse de fichier
    **
    ** Il faudra ouvir le fichier et lire --> get next line. 
    ** definir a quel section appartine la line :
    ** Section possible:
    **      room name et coordonnee
    **      connection
    **      modification
    **      comment
    ** au premier passage: reccupere le nom des rooms et creer une structure ,pour chaque room, 
    **      il faut recupere les nombres de connections de la room (pour mallocer la bonne taille pour les arrays of pointers)
    **      creer un arbre binaire pour ranger les rooms
    ** au deuxieme passage
    **      plus focus sur le connecction et store les connections dans le tableau creee
    **on retourne un arbre binaire ou chaque noeud est une structure room
    */

    return (0);
}

/*Tri la liste selon ascii table
t_lst_room *sort_list(t_lst_room *li)
{
    t_lst_room *head;
    char *swap;
    head = li;
    while (li->next != NULL)
    {
        if (ft_strcmp(li->name, li->next->name) >= 0)
        {
            swap = li->name;
            li->name = li->next->name;
            li->next->name = swap;
            li = head;
        }
        else
            li = li->next;
    }
    return (head);
}
*/

// /*Creer un struct room avec le nome de la room*/
// t_room *add_room(char *line,t_room *room)
// {
//     char *roomname;
//     t_room *element;

//     element = (t_room*)malloc(sizeof(t_room));
//     element->name = extract_name(line);
//     element->line = extract_line(line);
//     element->row  = extact_row(line);
//     //room = insert_node(roomname);//line doit renvoyer le nom de la room
//     //add coordonee en meme temps;
//     return (room);
// }



/* 
is valid line
*/

/*get number ant*/
/*  1er ligne 
    doit etre un chiffre et rien d autre
    pas despace en 1er
    pas de caractere apres le chiffre
*/
/*getroom*/
/* pas desapce avant le nom de la room
    1 espace entre les mots
    pas d espace apres le derniers
    doit etre composer de 3 mots
    1er : Nom de la room (peut etre n importe quoi)
    2eme : un nombre
    3eme : un chiffre
    ne peut pas avoir de connection au milieu des rooms
    ne peut pas commencer par L ou #
*/
/*getignore line*/
/* commence par #
/*getmodifououcomment*/
/*commence par un ##
pas d espace avant pas despace a la fin
modifie ligne suivante (pouvons faire un GNL independant de tout loop)

/*getconnection*/
/* est toujours compose de deux noms de rooms avec un tiret entre les deux
pas despace avant et apres
ne peut pas avoir de room au milieu de connextion
*/

/*toutes empty line ou not valide line stop le parsing eet si il ny as assez de data retourner ERROR*/
  /*Besoins d un depart, dune arrive, de fourmis et d un chemin*/

