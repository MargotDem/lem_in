/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:05:45 by briffard          #+#    #+#             */
/*   Updated: 2022/04/13 09:37:43 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char	*dst, const char	*src, size_t	len)
{
	if (ft_strlen(src) < len)
	{
		ft_strcpy(dst, src);
		ft_bzero(dst + ft_strlen(src), len - ft_strlen(src));
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
