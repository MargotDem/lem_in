/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:55:23 by briffard          #+#    #+#             */
/*   Updated: 2022/04/15 08:29:46 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t	n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	size_t			i;

	i = 0;
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
		n--;
	}
	return (0);
}
