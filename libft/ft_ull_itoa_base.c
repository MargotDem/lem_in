/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:48:08 by mde-maul          #+#    #+#             */
/*   Updated: 2022/03/15 17:48:10 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(unsigned long long int nb, int base)
{
	int		nb_size;

	nb_size = 0;
	while (nb)
	{
		nb = nb / base;
		nb_size++;
	}
	return (nb_size);
}

static void	make_string(char *str, int nb_size, unsigned long long int nb, \
	int base)
{
	unsigned long long int	tmp;
	int						i;

	i = 0;
	while (i < nb_size)
	{
		tmp = nb % base;
		if (tmp <= 9)
			str[nb_size - i - 1] = '0' + tmp;
		else
			str[nb_size - i - 1] = 'a' - 10 + tmp;
		nb = nb / base;
		i++;
	}
	str[nb_size] = '\0';
}

char	*ft_ull_itoa_base(unsigned long long int nb, int base)
{
	char	*nb_str;
	int		nb_size;

	nb_size = get_size(nb, base);
	if (nb == 0)
		nb_size = 1;
	nb_str = ft_strnew(nb_size);
	if (!nb_str)
		return (NULL);
	make_string(nb_str, nb_size, nb, base);
	return (nb_str);
}
