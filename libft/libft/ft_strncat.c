/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:05:11 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:45:57 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char	*s1, char	*s2, size_t	n)
{
	size_t			i;
	unsigned int	len;

	len = ft_strlen(s1);
	i = 0;
	if (s2[0] == '\0' )
		return (s1);
	while (i < n && s2[i] != '\0')
		s1[len++] = s2[i++];
	s1[len] = '\0';
	return (s1);
}
