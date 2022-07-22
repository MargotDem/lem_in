#include "parsing.h"

int define_solution(t_room *start, t_room *end)
{
	int tt_start_links = start->nb_links;
	int	tt_end_links = end->nb_links;

	if(tt_start_links > tt_end_links)
		return (tt_end_links);
	return (tt_start_links);
}

t_bfs	*create()
{
	t_bfs	*new;

	new = (t_bfs *)malloc(sizeof(new));
	if (!new)
		err_handling("malloc");
	new->to_visite = (t_room **)malloc(sizeof(t_room *) * 1);
	if (!new->to_visite)
		err_handling("malloc");
	new->size_to_visite = 0;
	return (new);
}

void	add_to_arr(t_room *node, t_bfs **bfs)
{
	int size = (*bfs)->size_to_visite;
	int i = 0;
	t_room	**dest;
	t_room	**original = (*bfs)->to_visite;

	dest = (t_room **)malloc(sizeof(t_room *));
	if (!dest)
		err_handling("malloc");
	while (i < size)
	{
		dest[i] = original[i];
		i++;
	}
	dest[i] = node;
	(*bsf)->size_to_visite += 1;
}

void	set_history(t_room *origin)
{
	origin->history[0] = origin;
}

void	cpy_history(t_room *room)
{
	t_room	*dest;

	dest = (t_room **)malloc(sizeof(t_room *) * room->size_history);
}

void	add_to_history(t_room *room, t_room *node)
{
	node->history = cpy_history(room);
}

void	add_to_visite(t_room *room,t_bfs **bsf)
{
	int		tt_links = room->nb_links;
	t_room	*node;
	while (i < tt_links)
	{
		node = room->links[i];
		if (node->visited == 0)
		{
			add_to_arr(node, bsf);
			node->visited == 1;
			add_to_history(room, node);
		}
		i++;
	}
}

void	test_solver(t_room *origin, t_data **data)
{
	int solution = define_solution(origin, search_for((*data)->exit_room), (*data));

	t_bfs	*bfs;

	bfs = create();

	add_to_visite(origin, &bfs);
	while (i < size_to_visite)
	{
		node = bfs->to_visiste[i];
		if (strcmp(node->name, "end") == 0)
		}
		add_to_visite(node, &bfs);
		i++;
	}
	/*
	 * on definit le nombre de chemin necessaire pour la solution optimal
	 *
	 * on verifie si les connexions de la node ou nous sommes est present danss
	 * l historic du chemin
	 *
	 * 	si oui on ajoute les nodes connectes a liste pour visite
	 * 	on ajoute les nodes connecter a la liste des chemins connus
	 *
	 * si la node ou nous sommes en = a la node de fin
	 * 	on lance le process pour verifier la solution
	 * 	les conditions de succes:
	 * 		si le nombre de chemins necssaire est > 2
	 * 		on doit etre comparer la combinaison des chemins sans node en commun
	 * on boucle jusqu a qu une solution soit valable ou que tous les chemins
	 * ont ete trouve
	 */


}