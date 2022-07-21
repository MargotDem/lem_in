/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:23:43 by mde-maul          #+#    #+#             */
/*   Updated: 2022/03/15 17:23:46 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(long long int n, int negative)
{
	int		size;

	size = 0;
	while (n)
	{
		size++;
		n = n / 10;
	}
	if (negative)
		size++;
	return (size);
}

static int	get_abs_value(long long int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

static void	make_string(char *str, int size, long long int n)
{
	int		i;

	i = 0;
	while (i < size)
	{
		str[size - i - 1] = get_abs_value(n % 10) + '0';
		n = n / 10;
		i++;
	}
	str[size] = '\0';
}

char	*ft_ll_itoa(long long int n)
{
	int		negative;
	int		size;
	char	*str;

	negative = 0;
	if (n < 0)
		negative = 1;
	size = get_size(n, negative);
	if (n == 0)
		size = 1;
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	make_string(str, size, n);
	if (negative)
		str[0] = '-';
	return (str);
}
