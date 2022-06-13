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
	start->x = 8;
	start->y = 1;
	start->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	start->links[0] = A;
	start->links[1] = D;
	start->links[2] = F;

	A->nb_links = 2;
	A->x = 4;
	A->y = 3;
	A->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	A->links[0] = start;
	A->links[1] = B;

	B->nb_links = 2;
	B->x = 1;
	B->y = 7;
	B->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	B->links[0] = A;
	B->links[1] = C;

	C->nb_links = 3;
	C->x = 4;
	C->y = 11;
	C->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	C->links[0] = B;
	C->links[1] = D;
	C->links[2] = end;

	D->nb_links = 2;
	D->x = 7;
	D->y = 6;
	D->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	D->links[0] = C;
	D->links[1] = start;

	F->nb_links = 3;
	F->x = 11;
	F->y = 3;
	F->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	F->links[0] = start;
	F->links[1] = E;
	F->links[2] = G;

	E->nb_links = 2;
	E->x = 10;
	E->y = 7;
	E->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	E->links[0] = F;
	E->links[1] = H;

	G->nb_links = 2;
	G->x = 15;
	G->y = 5;
	G->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	G->links[0] = F;
	G->links[1] = I;

	I->nb_links = 2;
	I->x = 17;
	I->y = 9;
	I->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	I->links[0] = G;
	I->links[1] = H;

	H->nb_links = 3;
	H->x = 13;
	H->y = 11;
	H->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	H->links[0] = end;
	H->links[1] = E;
	H->links[2] = I;

	end->x = 7;
	end->y = 14;

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

void	make_graph4(t_graph **graph)
{
	// 3 = middle path. 4 = left and right path
	t_graph	*start;
	t_graph	*A;
	t_graph	*B;
	t_graph	*C;
	t_graph	*D;
	t_graph	*E;
	t_graph	*F;
	t_graph	*end;
	
	start = create_node("start");
	A = create_node("4");
	B = create_node("1");
	C = create_node("2");
	D = create_node("5");
	E = create_node("6");
	F = create_node("3");
	end = create_node("end");

	start->nb_links = 2;
	start->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	start->links[0] = F;
	start->links[1] = B;

	A->nb_links = 2;
	A->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	A->links[0] = F;
	A->links[1] = C;

	B->nb_links = 3;
	B->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	B->links[0] = start;
	B->links[1] = D;
	B->links[2] = C;

	C->nb_links = 3;
	C->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	C->links[0] = B;
	C->links[1] = A;
	C->links[2] = end;

	end->nb_links = 2;
	end->links = (t_graph **)malloc(sizeof(t_graph *) * 1);
	end->links[0] = A;
	end->links[1] = B;


	D->nb_links = 2;
	D->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	D->links[0] = B;
	D->links[1] = E;

	E->nb_links = 2;
	E->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	E->links[0] = D;
	E->links[1] = end;

	F->nb_links = 2;
	F->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	F->links[0] = start;
	F->links[1] = A;

	*graph = start;
}

void	make_graph5(t_graph **graph)
{
	// 20 = 12 6 2
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
	t_graph	*J;
	t_graph	*K;
	t_graph	*L;
	t_graph	*M;
	t_graph	*N;
	t_graph	*O;
	t_graph	*P;
	t_graph	*Q;
	t_graph	*end;
	
	start = create_node("start");
	A = create_node("1");
	B = create_node("2");
	C = create_node("3");
	D = create_node("4");
	E = create_node("5");
	F = create_node("6");
	G = create_node("7");
	H = create_node("8");
	I = create_node("9");
	J = create_node("10");
	K = create_node("11");
	L = create_node("12");
	M = create_node("13");
	N = create_node("14");
	O = create_node("15");
	P = create_node("16");
	Q = create_node("17");
	end = create_node("end");

	start->nb_links = 3;
	start->links = (t_graph **)malloc(sizeof(t_graph *) * 3);
	start->links[0] = A;
	start->links[1] = B;
	start->links[2] = H;

	A->nb_links = 2;
	A->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	A->links[0] = start;
	A->links[1] = end;

	B->nb_links = 2;
	B->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	B->links[0] = start;
	B->links[1] = C;

	C->nb_links = 2;
	C->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	C->links[0] = B;
	C->links[1] = D;

	D->nb_links = 2;
	D->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	D->links[0] = C;
	D->links[1] = E;

	E->nb_links = 2;
	E->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	E->links[0] = D;
	E->links[1] = F;

	F->nb_links = 2;
	F->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	F->links[0] = F;
	F->links[1] = G;

	G->nb_links = 2;
	G->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	G->links[0] = F;
	G->links[1] = end;

	H->nb_links = 2;
	H->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	H->links[0] = start;
	H->links[1] = I;

	I->nb_links = 2;
	I->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	I->links[0] = H;
	I->links[1] = J;

	J->nb_links = 2;
	J->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	J->links[0] = I;
	J->links[1] = K;

	K->nb_links = 2;
	K->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	K->links[0] = J;
	K->links[1] = L;

	L->nb_links = 2;
	L->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	L->links[0] = K;
	L->links[1] = M;

	M->nb_links = 2;
	M->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	M->links[0] = L;
	M->links[1] = N;

	N->nb_links = 2;
	N->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	N->links[0] = M;
	N->links[1] = O;

	O->nb_links = 2;
	O->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	O->links[0] = N;
	O->links[1] = P;

	P->nb_links = 2;
	P->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	P->links[0] = O;
	P->links[1] = Q;

	Q->nb_links = 2;
	Q->links = (t_graph **)malloc(sizeof(t_graph *) * 2);
	Q->links[0] = P;
	Q->links[1] = end;

	*graph = start;
}
