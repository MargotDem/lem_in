/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:10:09 by mde-maul          #+#    #+#             */
/*   Updated: 2021/11/04 14:10:12 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	display_str(t_list *list_el)
{
	ft_putstr((char *)list_el->content);
	ft_putchar('\n');
}

void	ft_display_list_str(t_list *list)
{
	ft_lstiter(list, &display_str);
}
