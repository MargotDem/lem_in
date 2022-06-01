/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:54:41 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:33:44 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void	*dest, const void	*src, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (s == 0 && d == 0)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		if (d[i] == (unsigned char) c)
			return (dest + (i + 1));
		i++;
	}
	return (0);
}
