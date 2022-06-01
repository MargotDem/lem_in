/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 09:41:18 by briffard          #+#    #+#             */
/*   Updated: 2022/05/05 09:24:48 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printbits(void *ptr, int size)
{
	u_int8_t		*data;
	size_t			count;
	u_int8_t		i;
	u_int8_t		lu;

	lu = 1;
	count = 0;
	data = (u_int8_t *)(ptr) + (size - 1);
	while ((int)count < size)
	{
		i = 0;
		while (i < 8)
		{
			if (*data & (lu << (7 - i)))
				write (1, "1", 1);
			else
				write (1, "0", 1);
			i++;
		}
		write (1, " ", 1);
		data--;
		count++;
	}
	return (0);
}
