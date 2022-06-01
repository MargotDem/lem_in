/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:02:56 by mde-maul          #+#    #+#             */
/*   Updated: 2021/11/02 15:10:18 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*src_str;
	unsigned char		*dst_str;

	i = 0;
	if (!dst && !src)
		return (NULL);
	src_str = (const unsigned char *)src;
	dst_str = (unsigned char *)dst;
	while (i < n)
	{
		dst_str[i] = src_str[i];
		i++;
	}
	return ((void *)dst);
}
