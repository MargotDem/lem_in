/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlenght.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:47:44 by briffard          #+#    #+#             */
/*   Updated: 2022/05/03 14:38:33 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long int	ft_numlength(unsigned long long int n)
{
	unsigned long long	count;

	count = 0;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
