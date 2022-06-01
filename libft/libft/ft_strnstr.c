/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:06:29 by briffard          #+#    #+#             */
/*   Updated: 2022/01/07 09:47:27 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char	*needle, size_t len)
{
	size_t		i;
	size_t		j;
	char		*p;

	p = (char *) haystack;
	i = 0;
	if (needle[0] == '\0' || !needle)
		return (p);
	while (p[i] != '\0')
	{
		j = 0;
		while (p[i + j] == needle[j] && p[i + j] != '\0' && len > (i + j))
		{	
			if (needle[j + 1] == '\0')
				return ((char *)&p[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
