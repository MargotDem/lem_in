/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:19:36 by mde-maul          #+#    #+#             */
/*   Updated: 2021/11/02 19:19:39 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*src_str;
	unsigned char	*dst_str;

	if (!dst && !src)
		return (NULL);
	src_str = (unsigned char *)src;
	dst_str = (unsigned char *)dst;
	i = 0;
	while (i < len)
	{
		if (src < dst)
			dst_str[len - i - 1] = src_str[len - i - 1];
		else
			dst_str[i] = src_str[i];
		i++;
	}
	return (dst);
}
