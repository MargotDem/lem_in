#include "parsing.h"
static t_room *create_root(t_room **li, int size);

static t_room *create_root(t_room **li, int size)
{
    int i;
    
    i = 0;
    while(i <  size)
    {
        *li = (*li)->next;
        i++;
    }
    return (*li);
}

t_room *createtree(t_room **li, int size_lst)
{
    /*definir la racine de notre arbre
    root = size_lst / 2;

    definir les branches exterieurs 
        branche de gauche
             mediangauche = parent - minsize(0) / 2 - 
             on repete jusqu a mediangauche - minsze <= 2;
        branche de droite
            // median droite = ((maxsize - parent) / 2) + parent 
            on repete jusqu a maxsize - median droite <= 2

        pour les branches interieurs gauches
            median value = ((parent - fils) / 2) + fils
            on repete jusqu a medin value <= 2;

        pour les branches interieurs droite
            median value = ((fils - parent) / 2) + parents
            on repete jusqu a medin value <= 2;
    */
   t_room *tree_head;
   tree_head = create_root(li, size_lst);

   printf("room name--> %s\n", tree_head->name);
   return (tree_head);
}