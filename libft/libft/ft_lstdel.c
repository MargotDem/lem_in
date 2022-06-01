/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:09:40 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:32:38 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*tmp;

	next = *alst;
	tmp = *alst;
	while (next)
	{
		next = (*alst)->next;
		ft_lstdelone(&*alst, del);
		*alst = next;
	}
	*alst = tmp;
	*alst = NULL;
}
