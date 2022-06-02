#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct s_tree {
    int value;
    struct s_tree  *left;
    struct s_tree  *right;
    struct s_tree  *parent;
} t_tree;


t_tree     *new_tree(int x)
{
    t_tree *tr;

    tr = malloc(sizeof(*tr));
    if (tr == NULL)
    {
        write (2, "ERROR MALLOC\n", 13);
        exit(EXIT_FAILURE);
    }
    tr->value = x;
    tr->left = NULL;
    tr->right = NULL;
    tr->parent = NULL;
    printf("Creation de %d\n", x);
    return (tr);
}

void clean_tree(t_tree *tr)
{
    if (tr == NULL)
        return ;
    printf("Suppression de %d\n", tr->value);

    clean_tree(tr->left);
    clean_tree(tr->right);

    free(tr);

}

t_tree *join_tree(t_tree *left, t_tree *right, int node)
{
    t_tree *tr = new_tree(node);
    tr->left = left;
    tr->right = right;

    if (left != NULL)
        left->parent = tr;
    if (right != NULL)
        right->parent = tr;
    
    return (tr);
}

t_tree *insert(t_tree *element,t_tree *tr)
{
    t_tree *temp;
    temp = tr;
    if (element->value < temp->value && temp->left != NULL)
        insert(element, temp->left);
    else if (element->value > temp->value && temp->right != NULL)
        insert(element, temp->right);
    element->parent = temp;
    if (element->value < temp->value)
        temp->left = element;
    else if (element->value > temp->value)
        temp->right = element; 
    return (tr);
}

t_tree *insert_node(t_tree *tr, int node)
{
    t_tree *element = new_tree(node);

    if (tr == NULL)
        return (element);
    if (node < tr->value)
        insert(element, tr->left);
    else
        insert(element,tr->right);
    return (tr);    
}


/* post fix arbre droite puis arbre gauche*/
void print_tree_postfix(t_tree *tr)
{
    if (tr == NULL)
        return ;
    if (tr->parent != NULL)
        printf("(%d) -> %d \n", tr->parent->value, tr->value);
    else
        printf("(%d)\n", tr->value);
    if (tr->right != NULL)
        print_tree_postfix(tr->right);
    if (tr->left != NULL )
        print_tree_postfix(tr->left);
}


/*Print en prefix de gauche a droite*/
void print_tree_prefix(t_tree *tr)
{
    if (tr == NULL)
        return ;
    if (tr->parent != NULL)
        printf("(%d) -> %d \n", tr->parent->value, tr->value);
    else
        printf("(%d)\n", tr->value);
    if (tr->left != NULL )
        print_tree_prefix(tr->left);
    if (tr->right != NULL)
        print_tree_prefix(tr->right);
}

/*Compte le nombre de noeud (racine inclus)*/
int count_node(t_tree *tr)
{
    if (tr == NULL)
        return (0);
    
    return (count_node(tr->left) + count_node(tr->right) + 1);
}

int main(void)
{
    // int values[] = {4 , 5, 6, 7, 9, 10, 3, 85, 12};
    // int i = 0;
    // int length = 9;
    // int median_value = length;
    // t_node *node;

    // median_value = (median_value / 2);
    // while (i < 9)
    //     {
    //         push_back(node,values[median_value])
    //         i++;        
    //     }

    t_tree *new;

    // new = new_tree(5); creer une node left et right pointant sur null
    // new = join_tree(new_tree(2), new_tree(4), 6); creer un arbre racine 6 2 a gauche et 4 a droite
    new = join_tree(join_tree(new_tree(8),new_tree(3), 2), new_tree(4), 6);
    new = insert_node(new, 7);
    //                  ->ARBRE GAUCHE                    <>ARBRE DROITE><RACINE>
    print_tree_prefix(new);
    printf("===============\n");
    print_tree_postfix(new);
    printf("Il  y a %d node dans l arbre new\n",count_node(new));
    clean_tree(new);
    return (0);
}






// int median_value(int tab[], int size)
// int arraySize(int *array)
//   {
//       return (sizeof(array)/sizeof(int));
//   }

/*Create a new element with coordonne and put it in a linked list*/
// t_dlist	push_back_list(t_dlist li, char *tetriminos)
// {
// 	t_tetri		*element;
// 	int i = 0;

// 	element = malloc(sizeof(*element));
// 	//element = allocate_memory(*element);
// 	element->coordonnee = (int **) malloc((sizeof(int *) *4) + 1);
// 	element->temp = (int **) malloc((sizeof(int *) *4) + 1);
// 	while(i < 5)
// 	{
// 		element->coordonnee[i] = (int *) malloc((sizeof(int) * 4) + 1);
// 		element->temp[i] = (int *) malloc((sizeof(int) * 4) + 1);
// 		if(!element->coordonnee[i] || !element->temp[i])
// 			exit(EXIT_FAILURE);
// 		i++;
// 	}
// 	if (check_return(element))
// 			return(NULL);
// 	element->coordonnee = save_coordonnee(tetriminos, element->coordonnee);
// 	element->coordonnee = align(element->coordonnee,check_coordonnee(element->coordonnee));
// 	element->temp = cp_to(element->temp, element->coordonnee);
// 	element->next = NULL;
// 	if (is_empty_dlist(li))
// 	{
// 		li = malloc(sizeof(*li));
// 		if (check_return_dlist(li))
// 			exit(EXIT_FAILURE);
// 		li->length = 0;
// 		li->begin = element;
// 		li->end = element;
// 	}
// 	else
// 	{
// 		li->end->next = element;
// 		element->back = li->end;
// 		li->end = element;
// 	}
// 	li->length++;
// 	return(li);
// }

// t_node	*push_back(t_node *li, int value)
// {
// 	t_node		*element;
// 	t_node		*temp;

// 	element = (t_node *)malloc(sizeof(element));
// 	element->value = value;
// 	element->right = NULL;
//     element->left = NULL;
// 	if (!li)
// 		return (element);
// 	temp = li;
//     while (temp->left != NULL && temp->)
// 		{
//             if (temp->value < value)
//                 temp = temp->left;
//             else 
//             temp = temp->right;
// 	temp = element;
// 	return(li);
// }