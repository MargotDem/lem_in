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
    printf("Creation de %s\n", tr->name);
    return (tr);
}


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


t_room *insert_node(t_room *tr, char *line)
{
    t_room *element = new_tree(line);

    if (tr == NULL)
        return (element);
    if (ft_strcmp(element->name,tr->name) < 0) // check if room est plus grand ou plus en ASCII plus petit va vers la gauche plsu vers la droite
        insert(element, tr->left);
    else
        insert(element,tr->right);
    return (tr);    
}

/* Lis depuis le fd = 0 et check chaque ligne */
t_room *mapreader(int fd, t_room *room_tree)
{
    char *line;
    while (get_next_line(fd, &line))// checker sur fd lire 
    {
        if (is_room(line))
            insert_node(room_tree, line);
        // else if (is_comment(line))
        //     pass_line();
        // else if (is_modif(line))
        //     to_modif(line, room_tree);
        // else if (is_connection(line))
        //     counter_connection(line, room_tree);
    }
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