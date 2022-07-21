/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:47:04 by mde-maul          #+#    #+#             */
/*   Updated: 2022/03/15 17:47:06 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int nb, int base, int negative)
{
	int		nb_size;

	nb_size = 0;
	while (nb)
	{
		nb = nb / base;
		nb_size++;
	}
	if (negative)
		nb_size++;
	return (nb_size);
}

static void	make_string(char *str, int nb_size, int nb, int base)
{
	int	tmp;
	int	i;

	i = 0;
	while (i < nb_size)
	{
		tmp = ft_abs(nb) % base;
		if (tmp <= 9)
			str[nb_size - i - 1] = '0' + tmp;
		else
			str[nb_size - i - 1] = 'a' - 10 + tmp;
		nb = nb / base;
		i++;
	}
	str[nb_size] = '\0';
}

char	*ft_itoa_base(int nb, int base)
{
	char	*nb_str;
	int		nb_size;
	int		negative;

	negative = 0;
	if (nb < 0)
		negative = 1;
	nb_size = get_size(nb, base, negative);
	if (nb == 0)
		nb_size = 1;
	nb_str = ft_strnew(nb_size);
	if (!nb_str)
		return (NULL);
	make_string(nb_str, nb_size, nb, base);
	if (negative)
		nb_str[0] = '-';
	return (nb_str);
}
