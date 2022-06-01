/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:03:47 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:44:42 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dlen;

	i = 0;
	dlen = ft_strlen(dst);
	j = dlen;
	if (dstsize < (size_t)ft_strlen(dst))
		return ((size_t)ft_strlen(src) + dstsize);
	while ((dstsize > j + 1) && src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	return ((size_t)ft_strlen(src) + dlen);
}
