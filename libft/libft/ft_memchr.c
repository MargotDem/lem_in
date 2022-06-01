/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:55:02 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:34:02 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void	*s, int c, size_t	n)
{
	size_t			i;
	unsigned char	*src;
	unsigned char	d;

	src = (unsigned char *)s;
	d = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*src == d)
			return (src);
		src++;
		i++;
	}
	return (0);
}
