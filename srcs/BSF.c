/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 07:56:02 by briffard          #+#    #+#             */
/*   Updated: 2022/07/08 08:38:38 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


void	a_visted(t_room *origin, t_room **tab, t_bsf **bsf)
{
    int i;
/*    t_room **dest;


	dest = (t_room **)malloc(sizeof(t_room *) * 1000);
	i = -1;
	while (++i < 1000)
		dest[i] = NULL;
*/
	i = 0;
	while ( i < origin->nb_links)
	{
		if (origin->links[i]->visited == 0)
		{
			(*bsf)->to_visite[(*bsf)->size_n] = tab[i];
			(*bsf)->size_n += 1;
			origin->links[i]->visited = TRUE;
		}
		i++;
	}
   /* i = 0;
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
    }*/
   // return (dest);
}

void    bsf(t_room *origin, t_data **data)
{
    int i;
    int size;
    t_room *node;
    t_bsf *bsf;
	
    bsf = NULL;
    bsf = (t_bsf *)malloc(sizeof(bsf));
	bsf->to_visite = (t_room **)malloc(sizeof(t_room *) * 1000);
	i = -1;
	while (++i < 1000)
		bsf->to_visite[i] = NULL;
    bsf->size_n = 0;
	origin->visited = TRUE;

    i = 0;
    a_visted(origin, origin->links, &bsf); // tableaux de pointeur qui continet les nodes a visiter
    size = bsf->size_n;

    while ( i < (*bsf).size_n)
    {
        node = bsf->to_visite[i];
        printf("NODE -> %s || i-> %d\n", node->name, i);
        if (ft_strcmp(node->name, (*data)->exit_room) == 0)
        {
            printf("LAST NODE  is next\n");
            i++;
			node = bsf->to_visite[i];
			printf("NEW NOde -> %s\n", node->name );
            if (i == bsf->size_n)
                break;
        }
		a_visted(node, node->links, &bsf);
		i++;
    }
    printf("RETURN ARR DES CHEMIN TROUVER\n");
}


