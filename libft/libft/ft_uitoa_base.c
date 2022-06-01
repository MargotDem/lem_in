/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:59:59 by briffard          #+#    #+#             */
/*   Updated: 2022/05/03 14:38:33 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa_base(unsigned long long number, int base)
{
	int		index;
	char	*str;

	index = 0;
	str = ft_strnew(ft_numlength(number) + 1);
	if (!str)
		return (NULL);
	if (number == 0)
	{
		ft_strdel(&str);
		return (ft_strdup("0"));
	}
	while (number > 0)
	{
		str[index] = BASE[number % base];
		number = number / base;
		index++;
	}
	str[index] = '\0';
	ft_reverse_str(str);
	return (str);
}
