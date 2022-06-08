#include "lem_in.h"

typedef struct s_room {
	char *name;
	struct s_room *left;
	struct s_room *right;
	struct s_room *parent;
} t_room;

int     open_file(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(2, "ERROR OPEN FILE", 14);
        exit  (EXIT_FAILURE);
    }
    return (fd);
}

t_room *read_file(int fd)
{
    char *line;
    t_room *room;

    while (get_next_line(fd, &line))// checker sur fd lire 
    {
        /*creation dun pointeur room*/
        if (is_room(line))
            add_room(line,room);
        else if (is_comment(line))
            pass_line();
        else if (is_modif(line))
            to_modif(line, room);
        else if (is_connection(line))
            counter_connection(line, room);
    }
    return(room);
}

t_room *add_room(char *line,t_room *room)
{
    room = insert_node(line);//line doit renvoyer le nom de la room
    //add coordonee en meme temps;
    return (room);
}

int is_bigger(char *name, char *ref)
{
    if (name > ref)
        return (1);
    return (0);
}


t_room     *new_tree(char *room_name)
{
    t_room *tr;

    tr = malloc(sizeof(*tr));
    if (tr == NULL)
    {
        write (2, "ERROR MALLOC\n", 13);
        exit(EXIT_FAILURE);
    }
    tr->name = ft_strcpy(room_name);
    tr->left = NULL;
    tr->right = NULL;
    tr->parent = NULL;
    printf("Creation de %s\n", tr->name);
    return (tr);
}


void clean_tree(t_room *tr)
{
    if (tr == NULL)
        return ;
    printf("Suppression de %d\n", tr->name);

    clean_tree(tr->left);
    clean_tree(tr->right);

    free(tr);

}

t_room *insert(t_room *element,t_room *tr)
{
    t_room *temp;
    temp = tr;
    if (element->name < temp->name && temp->left != NULL) // creer un comparateur ascii
        insert(element, temp->left);
    else if (element->name > temp->name && temp->right != NULL)
        insert(element, temp->right);
    element->parent = temp;
    if (element->name < temp->name)
        temp->left = element;
    else if (element->name > temp->name)
        temp->right = element; 
    return (tr);
}

t_room *insert_node(t_room *tr, char *room_name)
{
    t_room *element = new_tree(room_name);

    if (tr == NULL)
        return (element);
    if (room_name < tr->name) // check if room est plus grand ou plus en ASCII plus petit va vers la gauche plsu vers la droite
        insert(element, tr->left);
    else
        insert(element,tr->right);
    return (tr);    
}


int main(int argc, char ** argv)
{
    /*
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
    **
    */

    return (0);
}