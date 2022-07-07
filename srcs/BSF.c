#include "parsing.h"


t_room **a_visted(t_room *origin, t_room **tab, t_bsf **bsf)
{
    int i, j,l;
    int x;
    t_room **dest;

    i = 0;
    // printf("origin->nb_links => %d\n",origin->nb_links);
    while (i < origin->nb_links)
    {
        // printf("origin->visited=> %d\n", origin->links[i]->visited);
        if (origin->links[i]->visited ==  FALSE)
        {
            x = 0;
            // printf("origin->links[%d]->nb_links -> %d\n", i, origin->links[i]->nb_links );
            // printf("(*bsf)->size_n -> %d\n", (*bsf)->size_n);
            // printf (" add = %d\n", ((*bsf)->size_n + origin->links[i]->nb_links));
            while ( x < origin->links[i]->nb_links)
            {
               dest = (t_room **)malloc(sizeof(t_room *) * ((*bsf)->size_n + origin->links[i]->nb_links));
               j = 0;
               while (j < (*bsf)->size_n)
               {
                    dest[j] = tab[j];
                    j++;
               }
               l = 0;
               while (j < ((*bsf)->size_n + origin->links[i]->nb_links))
               {
                    dest[j] = origin->links[l];
                    j++;
                    l++;
               }
                x++;
            }
        (*bsf)->size_n = j;
        }
        i++;
    }
    return (dest);
}

void    bsf(t_room *origin, t_data **data)
{
    int i;
    int size;
    t_room *node;
    t_bsf *bsf;

    bsf = NULL;
    bsf = (t_bsf *)malloc(sizeof(bsf));
    bsf->to_visite = (t_room **)malloc(sizeof(t_room*) * 1);
    bsf->to_visite[0] = NULL;
    bsf->size_n = 0;

    i = 0;
    bsf->to_visite = a_visted(origin, origin->links, &bsf); // tableaux de pointeur qui continet les nodes a visiter
    size = bsf->size_n;

    while ( i < size)
    {
        node = bsf->to_visite[i];
        printf("NODE -> %s || i-> %d\n", node->name, i);
        if (ft_strcmp(node->name, (*data)->exit_room))
        {
            printf("LAST NODE  is next\n");
            i++;
            if (i == size)
                break;
        }
        if (!node->visited)
            bsf->to_visite = a_visted(node, node->links, &bsf);
        node->visited = TRUE;
        i++;
    }
    printf("RETURN ARR DES CHEMIN TROUVER\n");
}


