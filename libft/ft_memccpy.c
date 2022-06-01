/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:58:50 by mde-maul          #+#    #+#             */
/*   Updated: 2021/11/02 18:58:59 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	const unsigned char	*src_str;
	unsigned char		*dst_str;

	i = 0;
	if (!dst && !src)
		return (dst);
	src_str = (const unsigned char *)src;
	dst_str = (unsigned char *)dst;
	while (i < n)
	{
		dst_str[i] = src_str[i];
		if (src_str[i] == (unsigned char)c)
			return ((void *)(&dst_str[i + 1]));
		i++;
	}
	return (NULL);
}
