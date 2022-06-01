/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:08:49 by briffard          #+#    #+#             */
/*   Updated: 2022/05/03 14:38:33 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlength(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = n * -1;
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_l_itoa(long number)
{
	long	i;
	char	*str;

	i = numlength(number);
	if (number == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (number < 0)
	{
		str[0] = '-';
		number = number * -1;
	}
	while (number > 0)
	{
		str[i--] = 48 + (number % 10);
		number = number / 10;
	}
	return (str);
}
