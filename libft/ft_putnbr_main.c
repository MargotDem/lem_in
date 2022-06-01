/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:57:01 by mde-maul          #+#    #+#             */
/*   Updated: 2021/11/01 10:57:04 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_main(int n, int where)
{
	char	c;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(where, "-2", 2);
			ft_putnbr_main(147483648, where);
		}
		else
		{
			write(where, "-", 1);
			ft_putnbr_main(-n, where);
		}
	}
	else
	{
		if (n > 9)
		{
			ft_putnbr_main(n / 10, where);
		}
		c = n % 10 + '0';
		write(where, &c, 1);
	}
}
