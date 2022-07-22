#include "parsing.h"

int define_solution(t_room *start, t_room *end)
{
	int tt_start_links = start->nb_links;
	int	tt_end_links = end->nb_links;

	if(tt_start_links > tt_end_links)
		return (tt_end_links);
	return (tt_start_links);
}



void	test_solver(t_room *origin, t_data **data)
{
	int solution = define_solution(origin, search_for((*data)->exit_room), (*data));


	add_to_visite(origin);

	while (i < size_to_visite)
	{
		node = to_visiste[i];
		if (node == end)
		{
			if (path nexite pas)
				save_paths;
			else
			{
				reset();
				i = 0;
				add_to_visite(origin);
				node = to_visite[0]; 
			}
		}
		add_to_visite(node);
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