/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:54:07 by briffard          #+#    #+#             */
/*   Updated: 2022/05/05 08:51:21 by briffard         ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	long	k;
	int		i;
	char	*str;

	k = n;
	i = numlength(k);
	if (k == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (k < 0)
	{
		str[0] = '-';
		k = k * -1;
	}
	while (k > 0)
	{
		str[i--] = 48 + (k % 10);
		k = k / 10;
	}
	return (str);
}
