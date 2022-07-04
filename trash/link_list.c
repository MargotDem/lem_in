#include "lem_in.h"

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