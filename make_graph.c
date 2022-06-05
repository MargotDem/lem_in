/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:42:23 by mde-maul          #+#    #+#             */
/*   Updated: 2022/06/05 17:42:25 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	make_graph(t_graph **graph)
{
	t_graph	*start;
	t_graph	*A;
	t_graph	*B;
	t_graph	*C;
	t_graph	*D;
	t_graph	*E;
	t_graph	*F;
	t_graph	*G;
	t_graph	*H;
	t_graph	*I;
	t_graph	*end;
	
	start = create_node("start");
	A = create_node("A");
	B = create_node("B");
	C = create_node("C");
	D = create_node("D");
	E = create_node("E");
	F = create_node("F");
	G = create_node("G");
	H = create_node("H");
	I = create_node("I");
	end = create_node("end");

	start->nb_links = 3;
	start->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	start->links[0] = A;
	start->links[1] = D;
	start->links[2] = F;

	A->nb_links = 2;
	A->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	A->links[0] = start;
	A->links[1] = B;

	B->nb_links = 2;
	B->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	B->links[0] = A;
	B->links[1] = C;

	C->nb_links = 3;
	C->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	C->links[0] = B;
	C->links[1] = D;
	C->links[2] = end;

	D->nb_links = 2;
	D->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	D->links[0] = C;
	D->links[1] = start;

	F->nb_links = 3;
	F->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	F->links[0] = start;
	F->links[1] = E;
	F->links[2] = G;

	E->nb_links = 2;
	E->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	E->links[0] = F;
	E->links[1] = H;

	G->nb_links = 2;
	G->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	G->links[0] = F;
	G->links[1] = I;

	I->nb_links = 2;
	I->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	I->links[0] = G;
	I->links[1] = H;

	H->nb_links = 3;
	H->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	H->links[0] = end;
	H->links[1] = E;
	H->links[2] = I;

	*graph = start;
}

void	make_graph2(t_graph **graph)
{
	t_graph	*start;
	t_graph	*A;
	t_graph	*B;
	t_graph	*end;
	
	start = create_node("start");
	A = create_node("2");
	B = create_node("3");
	end = create_node("end");

	start->nb_links = 1;
	start->links = (t_graph **)malloc(sizeof(t_graph *) * 1);
	start->links[0] = A;

	A->nb_links = 2;
	A->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	A->links[0] = start;
	A->links[1] = B;

	B->nb_links = 2;
	B->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	B->links[0] = A;
	B->links[1] = end;

	end->nb_links = 1;
	end->links = (t_graph **)malloc(sizeof(t_graph *) * 1);
	end->links[0] = B;

	*graph = start;
}

void	make_graph3(t_graph **graph)
{
	t_graph	*start;
	t_graph	*A;
	t_graph	*B;
	t_graph	*C;
	t_graph	*end;
	
	start = create_node("start");
	A = create_node("1");
	B = create_node("3");
	C = create_node("2");
	end = create_node("end");

	start->nb_links = 2;
	start->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	start->links[0] = A;
	start->links[1] = C;

	A->nb_links = 2;
	A->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	A->links[0] = start;
	A->links[1] = end;

	B->nb_links = 2;
	B->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	B->links[0] = C;
	B->links[1] = end;

	C->nb_links = 2;
	C->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	C->links[0] = start;
	C->links[1] = B;

	end->nb_links = 2;
	end->links = (t_graph **)malloc(sizeof(t_graph *) * 1);
	end->links[0] = A;
	end->links[1] = B;

	*graph = start;
}
