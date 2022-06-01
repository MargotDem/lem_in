/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randomnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:42:02 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:40:49 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_randomnbr(void)
{
	int	nbr;
	int	min;
	int	max;

	min = 1;
	max = 100;
	srand((time(NULL)));
	nbr = (rand() % (max - min + 1)) + min;
	return (nbr);
}
