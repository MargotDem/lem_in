/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:55:41 by briffard          #+#    #+#             */
/*   Updated: 2022/04/13 09:37:09 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dest, const void	*src, size_t n)
{
	unsigned char	*pdst;

	if (n && (!dest && !src))
		return (NULL);
	pdst = (unsigned char *)dest;
	while (n--)
		*pdst++ = *(unsigned char *)src++;
	return (dest);
}
