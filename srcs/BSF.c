/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 07:56:02 by briffard          #+#    #+#             */
/*   Updated: 2022/07/08 13:30:43 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
void	add_historic(t_room *origin, t_room *to, t_bsf **bsf)
{
	(*bsf)->paths[i] =  
}

*/
void	a_visted(t_room *origin, t_room **tab, t_bsf **bsf)
{
    int i;
	int counter;
/*    t_room **dest;


	dest = (t_room **)malloc(sizeof(t_room *) * 1000);
	i = -1;
	while (++i < 1000)
		dest[i] = NULL;
*/
	i = 0;
	counter = 0;
	while ( i < origin->nb_links)
	{
		if (origin->links[i]->visited == 0)
		{
			(*bsf)->to_visite[(*bsf)->size_n] = tab[i];
			(*bsf)->size_n += 1;
			origin->links[i]->visited = TRUE;
			counter += 1;
		}
		i++;
	}
		(*bsf)->node_parcourus += 1;
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
    int i, origin_nb_links = 0;
    t_room *node;
    t_bsf *bsf;
	
    bsf = NULL;
    bsf = (t_bsf *)malloc(sizeof(bsf));
	bsf->node_parcourus = 0;
	bsf->to_visite = (t_room **)malloc(sizeof(t_room *) * 2000);
/*	bsf->paths = (t_room **)malloc(sizeof(t_room *) * 50);
	i = -1;
	while (++i < 50)
		bsf->paths[i] = NULL;
*/	i = -1;
	while (++i < 1000)
		bsf->to_visite[i] = NULL;
    bsf->size_n = 0;
	bsf->deep = 0;
	origin->visited = TRUE;

    i = 0;
    a_visted(origin, origin->links, &bsf); // tableaux de pointeur qui continet les nodes a visi
	origin_nb_links = origin->nb_links;
	printf("X -> %d || n_par -> %d\n", origin_nb_links, bsf->node_parcourus);
    while ( i < (*bsf).size_n)
    {
		printf("X -> %d || n_par -> %d\n", origin_nb_links, bsf->node_parcourus);
		if (bsf->node_parcourus >= origin_nb_links)
		{
			bsf->node_parcourus = 0;
			bsf->deep += 1;
		}
        node = bsf->to_visite[i];
        printf("Checking links from NODE -> %s\n\t index-> %d || deep->%d\n", node->name, i, bsf->deep);
        if (ft_strcmp(node->name, (*data)->exit_room) == 0)
        {
            printf("%sLAST NODE  is next%s\n","\x1B[31m", "\033[0m");
            i++;
			if (i > bsf->size_n)
				break;
			node = bsf->to_visite[i];
			printf("NEW NOde -> %s\n", node->name );
        }
		a_visted(node, node->links, &bsf);
		origin_nb_links = node->nb_links;
		i++;
    }
    printf("RETURN ARR DES CHEMIN TROUVER\n");
}


