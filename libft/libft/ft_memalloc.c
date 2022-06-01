/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:54:24 by briffard          #+#    #+#             */
/*   Updated: 2022/04/12 16:57:32 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t	size)
{
	unsigned char	*arr;

	arr = (unsigned char *)malloc(size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, size);
	return (arr);
}
